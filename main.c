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
			path = ft_strjoin(ft_strcat(splited[j], "/"), cmd);
			if (access(path, X_OK) == 0)
				return (path);
			j++;
		}
		i++;
	}
	// char *str = ft_path(env);
	return (NULL);
}



void	ft_output_execution(mini_t *mini, char **env, char *cmd)
{
	mini->pid = fork();
	if (mini->pid == -1)
		exit(1);
	if (mini->pid == 0)
	{
		mini->args = ft_split(cmd, ' ');
		mini->path = ft_getpath(mini->args[0], env);
		dup2(mini->input, STDIN_FILENO);
		if (mini->flag_for_file_output == 1)
			dup2(mini->file_mulipipes, STDOUT_FILENO);
		else if (mini->flag_for_file_output == 2)
			dup2(mini->file_mulipipes, STDIN_FILENO);
		else if (mini->flag_for_file_output == 3)
			dup2(mini->fd[1], STDOUT_FILENO);
		else
		{
			dup2(STDOUT_FILENO, mini->fd[1]);
		}
		close(mini->fd[1]);
		close(mini->fd[0]);
		if (execve(mini->path, mini->args, env) == -1)
		{
			printf("command not found\n");
			exit(1);
		}
	}
}
void	ft_input_execution(mini_t *mini, char **env, char *cmd)
{
	mini->pid = fork();
	if (mini->pid == -1)
		exit(1);
	if (mini->pid == 0)
	{
		mini->args = ft_split(cmd, ' ');
		mini->path = ft_getpath(mini->args[0], env);
		if (mini->flag_for_file_input == 1)
			dup2(mini->file_mulipipes, STDIN_FILENO);
		else
			dup2(mini->input, STDIN_FILENO);
		dup2(mini->fd[1], STDOUT_FILENO);
		close(mini->fd[0]);
		if (execve(mini->path, mini->args, env) == -1)
		{
			printf("command not found\n");
			exit(1);
		}
	}
}

void	exec_first_cmd(mini_t *mini, char *cmd, char **env)
{
	mini->pid = fork();
	if (mini->pid == -1)
		exit(1);
	if (mini->pid == 0)
	{
		mini->args = ft_split(cmd, ' ');
		mini->path = ft_getpath(mini->args[0], env);
		dup2(mini->fd[1], STDOUT_FILENO);
		close(mini->fd[0]);
		if (execve(mini->path, mini->args, env) == -1)
		{
			printf("command not found\n");
			exit(1);
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
		exit(1);
	exec_first_cmd(mini, mini->piped_command[0], env);
	close(mini->fd[1]);
	i = 1;
	while (mini->piped_command[i])
	{
		wait(NULL);
		mini->input = mini->fd[0];
		if (pipe(mini->fd) == -1)
			exit(1);
		if (mini->piped_command[i + 1] == NULL)
		{
			mini->flag_for_file_output = 0;
			ft_output_execution(mini, env, mini->piped_command[i]);
		}
		else
			ft_input_execution(mini, env, mini->piped_command[i]);
		close(mini->fd[1]);
		i++;
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

void	cmd_exe(mini_t *mini, char **env)
{
	mini->cmd = readline(ANSI_COLOR_YELLOW "→" ANSI_COLOR_RESET " ");
	if (!mini->cmd)
    {
        printf("by\n");
        exit(0);
    }
    add_history(mini->cmd);
	if (ft_pipe_check(mini->cmd))
		multiple_cmds(mini, env);
	else
		normal_cmd(mini, env);
	free(mini->cmd);
}
void	execution(mini_t *mini, char **env)
{
    signals_handle();
	while (1)
	{
		cmd_exe(mini, env);
	    wait(NULL);
	}
	rl_clear_history();
}
int	main(int ac, char *av[], char *env[])
{
	mini_t mini;

	execution(&mini, env);
}