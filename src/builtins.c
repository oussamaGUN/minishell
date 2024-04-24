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
int	pwd(t_env *env)
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
		if (!ft_strcmp(p_env->key, "PWD"))
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
	s++;
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

int	set(t_env	*env, char *key, char *value)
{
	t_env *tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			tmp->value = value;
			return (0);
		}
		tmp = tmp->next;
	}
	t_env *new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->key = key;
	new->value = value;
	new->next = env->next;
	env->next = new;
	return (0);
}


int	export(t_token *lst, t_env *env)
{
	char *key;
	char *value;
	char **sp;

	while (*(++(lst->arr)))
	{
		sp = (char **)ft_malloc(0, &(env->mem), ft_split(*(lst->arr), '='));
		key = ft_strdup(sp[0]);
		if (!sp[1])
			value = ft_strdup("");
		else
			value = ft_strdup(sp[1]);
		if (!check_valid_identifier(key) || **(lst->arr) == '=')
		{
			if (key)
				free(key);
			if (value)
				free(value);
			if (sp)
				free(sp);
			return (printf("mini: export: `%s': not a valid identifier\n",
				*(lst->arr)), 1);
		}
		set(env, key, value);
	}
	return (0);
}



int	unset(t_token *lst, t_env *env)
{
	t_env *tmp;
	t_env *prev;
	t_env *next;
	while (*(++(lst->arr)))
	{
		tmp = env;
		prev = NULL;
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, *(lst->arr)))
			{
				if (prev)
					prev->next = tmp->next;
				else
					env = tmp->next;
				next = tmp->next;
				if (tmp->key)
					free(tmp->key);
				if (tmp->value)
					free(tmp->value);
				free(tmp);
				tmp = next;
			}
			else
			{
				prev = tmp;
				tmp = tmp->next;
			}
		}
	}
	return (0);
}

void	builtins(t_token *lst, t_env *env)
{

	if (!lst->arr[0])
		exit(1);
	if (!ft_strcmp(lst->arr[0], "pwd") || !ft_strcmp(lst->arr[0], "PWD"))
		exit(pwd(env));
	if (!ft_strcmp(lst->arr[0], "echo") || !ft_strcmp(lst->arr[0], "ECHO"))
		exit(echo(lst));
	if (!ft_strcmp(lst->arr[0], "cd") || !ft_strcmp(lst->arr[0], "CD"))
		exit(cd(lst->arr, env));
	if (!ft_strcmp(lst->arr[0], "env"))
		exit(print_env(env));
	if (!ft_strcmp(lst->arr[0], "export"))
		exit(export(lst, env));
	if (!ft_strcmp(lst->arr[0], "unset"))
		exit(unset(lst, env));
}

int	single_builtins(t_token *lst, t_env *env)
{
	if (!lst->arr[0])
		return 1;
	if (!ft_strcmp(lst->arr[0], "pwd") || !ft_strcmp(lst->arr[0], "PWD"))
		return (pwd(env));
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
