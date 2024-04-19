#include "main.h"

char	*get_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
int	pwd(t_token *lst, t_env *env)
{
	char *path;
	path = getcwd(NULL, 0);
	if (!path)
		perror("mini");
	else
		puts(ft_malloc(0, &(env->mem), path));
	return (0);
}
int cd(char **arr, t_env *env)
{
	if (!arr[1])
	{
		if (chdir(get_value(env, "HOME")) == -1)
			perror("mini");
	}
	else if (ft_strncmp(arr[1], "-", 1) == 0)
	{
		if (chdir(get_value(env, "OLDPWD")) == -1)
			perror("mini");
	}
	else if (ft_strncmp(arr[1], "~", 1) == 0)
	{
		if (chdir(get_value(env, "HOME")) == -1)
			perror("mini");
	}
	else
	{
		if (chdir(arr[1]) == -1)
			perror("mini");
	}
	return (0);
}
t_env *ft_update_pwd_env(t_env *env)
{
	char buff[4096];
	char *path;
	path = getcwd(buff, 4096);
	if (!path)
		return env;
	t_env *itter = env;
	while (itter)
	{
		if (ft_strncmp(itter->key, "PWD", 4) == 0)
			itter->value = ft_malloc(0, &(env->mem), ft_strdup(path));
		itter = itter->next;
	}
	return env;
}
t_env *ft_update_oldpwd_env(t_env *env)
{
	char buff[4096];
	char *path;
	path = getcwd(buff, 4096);
	if (!path)
		return env;
	t_env *itter = env;
	while (itter)
	{
		if (ft_strncmp(itter->key, "OLDPWD", 7) == 0)
			itter->value = ft_malloc(0, &(env->mem), ft_strdup(path));
		itter = itter->next;
	}
	return env;
}
int	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (1);
}
int ft_dashn(char *s)
{
	int i;

	i = 0;
	if (s[i] == '-')
		i++;
	else
		return 0;
	while (s[i])
	{
		if (s[i] != 'n')
			return 0;
		i++;
	}
	return 1;
}
int	echo(t_token *lst)
{
	int i;
	if (!lst->arr[1])
		printf("\n");
	else if (ft_dashn(lst->arr[1]))
	{
		i = 2;
		while (lst->arr[i])
			ft_putstr_fd(lst->arr[i++], 1);
	}
	else
	{
		i = 1;
		while (lst->arr[i])
		{
			ft_putstr_fd(lst->arr[i], 1);
			i++;
			if (lst->arr[i])
				ft_putstr_fd(" ", 1);
		}
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
int builtins(t_token *lst, t_env *env)
{
	if (!ft_strcmp(lst->arr[0], "cd") || !ft_strcmp(lst->arr[0], "CD"))
	{
		if (!cd(lst->arr, env))
			return (0);
	}
	else if (!ft_strcmp(lst->arr[0], "pwd") || !ft_strcmp(lst->arr[0], "PWD"))
	{
		return(pwd(lst, env));
	}
	else if (!ft_strcmp(lst->arr[0], "env"))
	{
		if (!print_env(env))
			return (0);
	}
	else if (!ft_strcmp(lst->arr[0], "echo") || !ft_strcmp(lst->arr[0], "ECHO"))
			return (echo(lst));
	return (1);
}
