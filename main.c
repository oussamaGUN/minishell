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
char *relative_path(char *s, char **env)
{
	int		i;
	int		j;
	char	*str;
	char	buff[4096];
	char	*path;
	i = 0;
	path = getcwd(buff, 4096);
    if (!path)
    {
        printf("bash: No such file or directory\n");
        return 0;
    }
	s++;
	str = ft_strjoin(path, s);
	if (access(str, X_OK) == 0)
	{
		return str;
	}
	return NULL;
}
char *normal_path(char *cmd, char **env)
{
	int		i;
	int		j;
	char	**str;
	char	**splited;
	char	*path;
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
	return NULL;
}
char	*ft_getpath(char *cmd, char **env)
{
	char *str;
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			return (NULL);
	}
	else if (cmd[0] == '.')
	{
		str = relative_path(cmd, env);
		if (str)
			return str;
		else
			return NULL;
	}
	else
	{
		str = normal_path(cmd, env);
		if (str)
			return str;
		else
			return NULL;
	}
	return (NULL);
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


int	cmd_exe(t_token *token, t_env *env)
{
	t_token *new_token;
	t_token *cmd_list;
	char *cmd;
	int flag;

	cmd = readline("→ ");
	if (!cmd || ft_strncmp(cmd ,"exit", 4) == 0)
	{
		printf("exit\n");
		return 1;
	}
	add_history(cmd);
	token = NULL;
	flag = tokenizer(cmd, &token);
	if (!flag)
		return 0;
	if (!ft_check_errors(token))
		return 0;
	new_token = expanding(token, env);
	cmd_list = ft_list(new_token, env);
	if (!cmd_list)
		return 0;
	if (!execution(cmd_list, env))
		return 0;
	return 0;
}
int	programme(t_token *token, t_env *env)
{
	int flag;

	flag = 0;
	while (1)
	{
		flag = cmd_exe(token, env);
		if (flag == 1)
			break;
	}
	// rl_clear_history();
	return 0;
}
void	list_for_env(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (lst && *lst)
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	else if (lst)
		*lst = new;
}
char *counter(int n)
{
	char *res = ft_itoa(n);
	int num = ft_atoi(res);

	return ft_itoa(num);
}
t_env *envir(char **envp)
{
	int		i;
	char	**arr;
	t_env	*env;
	t_env	*node;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		node = malloc(sizeof(t_env));
		node->next = NULL;
		arr = ft_split(envp[i], '=');
		if (!arr)
			return NULL;
		node->key = ft_strdup(arr[0]);
		if (ft_strncmp(node->key, "SHLVL", 6) == 0)
			node->value = ft_strdup("2");
		else
			node->value = ft_strdup(arr[1]);
		list_for_env(&env, node);
		i++;
	}
	return env;
}
int	main(int ac, char *av[], char *envp[])
{
	t_token			token;
	t_env			*env;

	env = envir(envp);
	exit_status = 0;
	programme(&token, env);
}