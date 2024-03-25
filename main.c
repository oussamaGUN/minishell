#include "main.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_getpath(char *cmd, char **env)
{
	int		i;
	int		j;
	char	**str;
	char	**splited;
	char	*path;

	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			return (NULL);
	}
	i = 0;
	while (env[i])
	{
		str = ft_split(env[i], '=');
		splited = ft_split(str[1], ':');
		j = 0;
		while (splited[j])
		{
			path = ft_strjoin(ft_strjoin(splited[j], "/"), cmd);
			if (access(path, X_OK) == 0)
				return (path);
			free(path);
			j++;
		}
		i++;
	}
	return (NULL);
}

void	ft_output_execution(mini_t *mini, char **env, char *cmd)
{
	int	i;

	mini->pid = fork();
	if (mini->pid == -1)
	{
		exit(EXIT_FAILURE);
	}
	if (mini->pid == 0)
	{
		
		mini->path = ft_getpath(mini->args[0], env);
		dup2(mini->input, STDIN_FILENO);
		close(mini->fd[1]);
		close(mini->fd[0]);
		if (execve(mini->path, mini->args, env) == -1)
		{
			free(mini->path);
			i = 0;
			while (mini->args[i])
				free(mini->args[i++]);
			free(mini->args);
			printf("command not found\n");
			exit(EXIT_FAILURE);
		}
	}
}
void	ft_input_execution(mini_t *mini, char **env, char *cmd)
{
	int	i;

	mini->pid = fork();
	if (mini->pid == -1)
	{
		exit(EXIT_FAILURE);
	}
	if (mini->pid == 0)
	{
		
		mini->path = ft_getpath(mini->args[0], env);
		dup2(mini->input, STDIN_FILENO);
		dup2(mini->fd[1], STDOUT_FILENO);
		close(mini->fd[0]);
		if (execve(mini->path, mini->args, env) == -1)
		{
			free(mini->path);
			i = 0;
			while (mini->args[i])
				free(mini->args[i++]);
			free(mini->args);
			printf("command not found\n");
			exit(EXIT_FAILURE);
		}
	}
}

void	exec_first_cmd(mini_t *mini, char *cmd, char **env)
{
	int	i;

	mini->pid = fork();
	if (mini->pid == -1)
	{
		exit(EXIT_FAILURE);
	}
	if (mini->pid == 0)
	{
		
		mini->path = ft_getpath(mini->args[0], env);
		dup2(mini->fd[1], STDOUT_FILENO);
		close(mini->fd[0]);
		if (execve(mini->path, mini->args, env) == -1)
		{
			free(mini->path);
			i = 0;
			while (mini->args[i])
				free(mini->args[i++]);
			free(mini->args);
			printf("command not found\n");
			exit(EXIT_FAILURE);
		}
	}
}

void	multiple_cmds(mini_t *mini, char **env)
{
	int	j;
	int	i;

	mini->piped_command = ft_split(mini->cmd, '|');
	j = 0;
	if (pipe(mini->fd) == -1)
	{
		exit(EXIT_FAILURE);
	}
	exec_first_cmd(mini, mini->piped_command[0], env);
	close(mini->fd[1]);
	i = 1;
	while (mini->piped_command[i])
	{
		wait(NULL);
		mini->input = mini->fd[0];
		if (pipe(mini->fd) == -1)
		{
			exit(EXIT_FAILURE);
		}
		if (mini->piped_command[i + 1] == NULL)
			ft_output_execution(mini, env, mini->piped_command[i]);
		else
			ft_input_execution(mini, env, mini->piped_command[i]);
		close(mini->fd[1]);
		i++;
	}
	close(mini->fd[0]);
	i = 0;
	while (mini->piped_command[i])
		free(mini->piped_command[i++]);
	free(mini->piped_command);
}
int	lstsize(t_token *lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		while (lst)
		{
			i++;
			lst = lst->next;
		}
	}
	return (i);
}
char **array(t_token *token)
{
	char **arr;
	int i = 0;
	int j = 0;
	int len = lstsize(token) + 1;
	arr = malloc(sizeof(char *) * (len + 1));
	while (token)
	{
		arr[i] = malloc(ft_strlen(token->content) + 1);
		while (token->content[j])
		{
			arr[i][j] = token->content[j];
			j++;
		}
		arr[i][j] = '\0';
		j = 0;
		i++;
		token = token->next;
	}
	arr[i] = NULL;
	return arr;
}
void	normal_cmd(t_token *token, char **env)
{
	int	pid;
	char *path;
	char **args;
	pid = fork();
	if (pid == 0)
	{
		args = array(token);
		path = ft_getpath(args[0], env);
		if (execve(path, args, env) == -1)
		{
			printf("bash: %s: command not found\n", args[0]);
			exit(EXIT_FAILURE);
		}
	}
}
char	*ft_pipe_check(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			return (cmd);
		i++;
	}
	return (NULL);
}
void ft_free(t_token **token, mini_t *mini)
{
	clear(token, del);
}

int	cmd_exe(mini_t *mini, t_token *token, char **env)
{
	t_token *new_token;
	mini->cmd = readline(ANSI_COLOR_YELLOW "→" ANSI_COLOR_RESET " ");
	if (!mini->cmd)
	{
		printf("exit\n");
		return 1;
	}
	add_history(mini->cmd);
	token = NULL;
	int flag = tokenizer(mini->cmd, &token);
	if (!flag)
		return 0;
	if (!ft_check_errors(token))
		return 0;
	new_token = expanding(token, env);
	if (open_files(new_token) == 1)
		return 0;
	// t_token *s = new_token;
	// while (s)
	// {
	// 	printf("%s %d\n", s->content, s->type);
	// 	s = s->next;
	// }





	// char **sf;
	// if (ft_strncmp(mini->cmd, "export", 6) == 0)
	// 	ft_export(mini, env);
	// else if (ft_pipe_check(mini->cmd))
	// 	multiple_cmds(mini, env);
	// else if (ft_strncmp(mini->cmd, "cd", 2) == 0 || ft_strncmp(mini->cmd, "exit", 4) == 0
	// 	|| ft_strncmp(mini->cmd, "pwd", 3) == 0)
	// 	check_builtin(mini, env);
	// else
		normal_cmd(new_token, env);
	return 0;
}
int	execution(mini_t *mini, t_token *token, char **env)
{
	int flag = 0;
	while (1)
	{
		flag = cmd_exe(mini, token, env);
		if (flag == 1)
			break;
		wait(NULL);

	}

	// rl_clear_history();
	return 0;
}
int	main(int ac, char *av[], char *env[])
{
	mini_t mini;
	t_token token;

	execution(&mini, &token, env);
}