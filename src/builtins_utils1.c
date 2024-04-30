/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:04:09 by melfersi          #+#    #+#             */
/*   Updated: 2024/04/30 13:22:37 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.h"

int	check_dash_n(char *s)
{
	if (*s != '-')
		return (0);
	s++;
	while (*s)
		if (*s++ != 'n')
			return (0);
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

int	export(char **arr, t_env *env)
{
	char	*key;
	char	*value;
	char	**sp;

	if (!*(arr + 1))
		return (print_sorted_export(env));
	while (*(++(arr)))
	{
		sp = ft_split(*(arr), '=');
		if (!sp[0])
		{
			printf("mini: export: `%s': not a valid identifier\n",
				*(arr));
			exit_status = 1;
			free(sp);
			continue ;
		}
		key = ft_strdup(sp[0]);
		if (!sp[1])
			value = ft_strdup("");
		else
			value = ft_strdup(sp[1]);
		if (!check_valid_identifier(key) || **(arr) == '=')
		{
			if (key)
				free(key);
			if (value)
				free(value);
			if (sp)
				free(sp);
			printf("mini: export: `%s': not a valid identifier\n",
				*(arr));
			exit_status = 1;
			continue ;
		}
		set(env, key, value);
	}
	return (exit_status);
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
		exit(pwd());
	if (!ft_strcmp(lst->arr[0], "echo"))
		exit(echo(lst));
	if (!ft_strcmp(lst->arr[0], "cd"))
		exit(cd(lst->arr, env));
	if (!ft_strcmp(lst->arr[0], "env"))
		exit(print_env(env));
	if (!ft_strcmp(lst->arr[0], "export"))
		exit(export(lst->arr, env));
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
		return (reset_io(lst), pwd());
	if (!ft_strcmp(lst->arr[0], "echo"))
		return (reset_io(lst), echo(lst));
	if (!ft_strcmp(lst->arr[0], "cd"))
		return (reset_io(lst), cd(lst->arr, env));
	if (!ft_strcmp(lst->arr[0], "env"))
		return (reset_io(lst), print_env(env));
	if (!ft_strcmp(lst->arr[0], "export"))
		return (reset_io(lst), export(lst->arr, env));
	if (!ft_strcmp(lst->arr[0], "unset"))
		return (reset_io(lst), unset(lst, env));
	if (!ft_strcmp(lst->arr[0], "exit"))
		return (exiting(lst));
	return (reset_io(lst), (-2));
}
