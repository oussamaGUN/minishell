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
int	 check_dash_n(char *s)
{
	if (*s != '-')
		return 0;
	*s++;
	while (*s)
		if (*s++ != 'n')
			return 0;
	return (1);
}
int	echo(t_token *lst)
{
	if (!*(lst->arr)++)
		printf("\n");
	else if (check_dash_n(*(lst->arr)++))
	{
		while (*(lst->arr))
			ft_putstr_fd(*(lst->arr)++, 1);
	}
	else
	{
		(lst->arr)--;
		while (*(lst->arr))
		{
			ft_putstr_fd(*(lst->arr)++, STDOUT_FILENO);
			if (*(lst->arr))
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (0);
}
// int	export(t_token *lst, t_env *env)
// {
// 	int i = 1;
// 	while (lst->arr[i])
// 	{
// 		char *key = ft_strtok(lst->arr[i], "=");
// 		char *value = ft_strtok(NULL, "=");
// 		if (!value)
// 			value = "";
// 		if (ft_strncmp(key, "OLDPWD", 7) == 0)
// 			env = ft_update_oldpwd_env(env);
// 		else if (ft_strncmp(key, "PWD", 4) == 0)
// 			env = ft_update_pwd_env(env);
// 		else
// 			env = ft_add_env(env, key, value);
// 		i++;
// 	}
// 	return (0);
// }

int builtins(t_token *lst, t_env *env)
{
	// if (!ft_strcmp(lst->arr[0], "pwd") || !ft_strcmp(lst->arr[0], "PWD"))
	// 	return(pwd(lst, env));
	// if (!ft_strcmp(lst->arr[0], "echo") || !ft_strcmp(lst->arr[0], "ECHO"))
	// 	return (echo(lst));
	// if (!ft_strcmp(lst->arr[0], "cd") || !ft_strcmp(lst->arr[0], "CD"))
	// 	return (cd(lst->arr, env));
	// if (!ft_strcmp(lst->arr[0], "env"))
	// 	return (print_env(env));
	// if (!ft_strcmp(lst->arr[0], "export"))
	// 	return (export(lst, env));
	return (1);
}
