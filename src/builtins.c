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
	printf("%s\n", ft_malloc(0, &(env->mem), ft_strdup(get_value(env, "PWD"))));
	return (0);
}
int cd(char **arr, t_env *env)
{
	if (!arr[1])
	{
		if (chdir(get_value(env, "HOME")) == (-1))
			return(perror("mini"), 1);
	}
	else if (ft_strncmp(arr[1], "-", 1) == 0)
	{
		if (chdir(get_value(env, "OLDPWD")) == (-1))
			return(perror("mini"), 1);
	}
	else if (ft_strncmp(arr[1], "~", 1) == 0)
	{
		if (chdir(get_value(env, "HOME")) == (-1))
			return(perror("mini"), 1);
	}
	else
	{
		if (chdir(arr[1]) == (-1))
			return (perror("mini"), 1);
	}
	return (0);
}
t_env *ft_update_pwd_env(t_env *env)
{
	char	*cwd;
	t_env	*p_env;;

	cwd = ft_malloc(0, &(env->mem), getcwd(NULL, 0));
	if (!cwd)
		return env;
	p_env = env;
	while (p_env)
	{
		if (ft_strncmp(p_env->key, "PWD", 4) == 0)
			p_env->value = cwd;
		p_env = p_env->next;
	}
	return (env);
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
	return (0);
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

bool	check_valid_identifier(char *s)
{
	if (!ft_isalpha(*s) && *s != '_')
		return (false);
	while (*s)
	{
		if (!ft_isalnum(*s))
			return (false);
		s++;
	}
	return (true);
}

t_env *set(t_token	*lst, t_env	*env, char *key, char *value)
{
	t_env	*envp;
	t_env	*tmp = env;

	envp = env;
	while (envp && key)
	{
		if (!ft_strcmp(envp->key, key))
		{
			envp->value = value;
			return (0);
		}
		envp = envp->next;
	}
	envp = ft_malloc(sizeof(t_env), &(env->mem), NULL);
	envp->key = key;
	envp->value = value;
	envp->next = NULL;
	list_for_env(&env, envp);
	tmp = env;
	while (tmp) 
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	
	return (env);
} 
int	export(t_token *lst, t_env *env)
{
	char *key;
	char *value;
	char **sp;

	while (*(++(lst->arr)))
	{
		sp = ft_malloc(0, &(env->mem), ft_split(*(lst->arr), '='));
		key = ft_malloc(0, &(env->mem), sp[0]);
		if (!sp[1])
			value = ft_malloc(0, &(env->mem), ft_strdup(""));
		else
			value = ft_malloc(0, &(env->mem), sp[1]);
		if (!check_valid_identifier(key))
			return (printf("mini: export: `%s': not a valid identifier\n",
				*(lst->arr)), 1);
		env = set(lst, env, key, value);
	}
	return (0);
}

void	builtins(t_token *lst, t_env *env)
{
	if (!lst->arr[0])
		return ;
	if (!ft_strcmp(lst->arr[0], "pwd") || !ft_strcmp(lst->arr[0], "PWD"))
		exit(pwd(lst, env));
	if (!ft_strcmp(lst->arr[0], "echo") || !ft_strcmp(lst->arr[0], "ECHO"))
		exit(echo(lst));
	if (!ft_strcmp(lst->arr[0], "cd") || !ft_strcmp(lst->arr[0], "CD"))
		exit(cd(lst->arr, env));
	if (!ft_strcmp(lst->arr[0], "env"))
		exit(print_env(env));
	if (!ft_strcmp(lst->arr[0], "export"))
		exit(export(lst, env));
}

int	single_builtins(t_token *lst, t_env *env)
{
	if (!lst->arr[0])
		return 1;
	if (!ft_strcmp(lst->arr[0], "pwd") || !ft_strcmp(lst->arr[0], "PWD"))
		return (pwd(lst, env));
	if (!ft_strcmp(lst->arr[0], "echo") || !ft_strcmp(lst->arr[0], "ECHO"))
		return (echo(lst));
	if (!ft_strcmp(lst->arr[0], "cd") || !ft_strcmp(lst->arr[0], "CD"))
		return (cd(lst->arr, env));
	if (!ft_strcmp(lst->arr[0], "env"))
		return (print_env(env));
	if (!ft_strcmp(lst->arr[0], "export"))
		return (export(lst, env));
	return (1);
}
