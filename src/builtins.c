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
	printf("%s\n", (char *)ft_malloc(0, &(env->mem),
			ft_strdup(get_value(env, "PWD"))));
	return (0);
}
int cd(char **arr, t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!arr[1])
	{
		if (chdir(get_value(env, "HOME")) == (-1))
			return(perror("mini"), 1);
		set(env, ft_strdup("OLDPWD"), cwd);
		return (0);
	}
	if (!ft_strcmp(arr[1], "-"))
		if (chdir(get_value(env, "OLDPWD")) == (-1))
			return(perror("mini"), 1);
	if (!ft_strcmp(arr[1], "~"))
		if (chdir(get_value(env, "HOME")) == (-1))
			return(perror("mini"), 1);
	if (ft_strncmp(arr[1], "~", 1) && ft_strncmp(arr[1], "-", 1))
		if (chdir(arr[1]) == (-1))
			return (perror("mini"), 1);
	set(env, ft_strdup("OLDPWD"), cwd);
	return (0);
}
t_env *ft_update_pwd_env(t_env *env)
{
	char	*cwd;
	t_env	*p_env;;
	cwd = getcwd(NULL, 0);
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
	if (!(*++(lst->arr)))
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
			if (tmp->value)
				free(tmp->value);
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

int	print_sorted_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
	return (0);
}

int	export(t_token *lst, t_env *env)
{
	char	*key;
	char	*value;
	char	**sp;

	if (!*(lst->arr + 1))
		return (print_sorted_export(env));
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
	t_env	*tmp;
	t_env	*prev;

	while (*(++(lst->arr)))
	{
		tmp = env;
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, *(lst->arr)))
			{
				if (tmp == env)
					env = env->next;
				else
					prev->next = tmp->next;
				free(tmp->key);
				free(tmp->value);
				free(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (0);
}

void	builtins(t_token *lst, t_env *env)
{
	if (!lst->arr[0])
		exit(1);
	if (!ft_strcmp(lst->arr[0], "pwd"))
		exit(pwd(env));
	if (!ft_strcmp(lst->arr[0], "echo"))
		exit(echo(lst));
	if (!ft_strcmp(lst->arr[0], "cd"))
		exit(cd(lst->arr, env));
	if (!ft_strcmp(lst->arr[0], "env"))
		exit(print_env(env));
	if (!ft_strcmp(lst->arr[0], "export"))
		exit(export(lst, env));
	if (!ft_strcmp(lst->arr[0], "unset"))
		exit(unset(lst, env));
	if (!ft_strcmp(lst->arr[0], "exit"))
		exit(exiting(lst));
}

int	reset_io(t_token *lst)
{
	dup2(lst->fd[0], STDIN_FILENO);
	dup2(lst->fd[1], STDOUT_FILENO);
	close(lst->fd[0]);
	close(lst->fd[1]);
	return (0);
}
int	exiting(t_token *lst)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (lst->arr[1])
	{
		if (lst->arr[1][0] == '-' || lst->arr[1][0] == '+')
			i++;
		while (lst->arr[1][i])
			if (!ft_isdigit(lst->arr[1][i++]))
			{
				printf("mini: exit: %s: numeric argument required\n",
					lst->arr[1]);
				exit(255);
			}
		if (lst->arr[2])
			return (printf("mini: exit: too many arguments\n"), 1);
		exit_status = ft_atoi(lst->arr[1]);
	}
	exit(exit_status % 256);
}

int	single_builtins(t_token *lst, t_env *env)
{
	lst->fd[0] = dup(STDIN_FILENO);
	lst->fd[1] = dup(STDOUT_FILENO);
	if (set_io(lst))
		return (reset_io(lst), 127);
	if (!lst->arr[0])
		return (reset_io(lst), 1);
	if (!ft_strcmp(lst->arr[0], "pwd"))
		return (pwd(env), reset_io(lst));
	if (!ft_strcmp(lst->arr[0], "echo"))
		return (echo(lst), reset_io(lst));
	if (!ft_strcmp(lst->arr[0], "cd"))
		return (cd(lst->arr, env), reset_io(lst));
	if (!ft_strcmp(lst->arr[0], "env"))
		return (print_env(env), reset_io(lst));
	if (!ft_strcmp(lst->arr[0], "export"))
		return (export(lst, env), reset_io(lst));
	if (!ft_strcmp(lst->arr[0], "unset"))
		return (unset(lst, env), reset_io(lst));
	if (!ft_strcmp(lst->arr[0], "exit"))
		return (exiting(lst));
	return (reset_io(lst), 1);
}
