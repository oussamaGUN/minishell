/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:01:37 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/09 18:24:21 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	print_sorted_export(t_env *env)
{
	sort_env(env);
	while (env)
	{
		if (env->visible)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
	return (0);
}

bool	export_spliting(char *arr, char **key, char **value)
{
	char	*tmp;

	tmp = ft_strchr(arr, '=');
	if (!ft_strlen(arr))
	{
		printf("mini: export: `%s': not a valid identifier\n", arr);
		g_exit_status = 1;
		free(arr);
		return (false);
	}
	if (tmp)
	{
		*tmp = '\0';
		*key = ft_strdup(arr);
		*value = ft_strdup(tmp + 1);
	}
	else
	{
		*key = ft_strdup(arr);
		*value = ft_strdup("");
	}
	free(arr);
	return (true);
}

int	export(char **arr, t_env *env)
{
	char	*key;
	char	*value;

	if (!*(arr + 1))
		return (print_sorted_export(env));
	while (*(++(arr)))
	{
		if (!export_spliting(ft_strdup(*arr), &key, &value))
			continue ;
		if (!check_valid_identifier(key) || **(arr) == '=')
		{
			if (key)
				free(key);
			if (value)
				free(value);
			printf("mini: export: `%s': not a valid identifier\n",
				*(arr));
			g_exit_status = 1;
			continue ;
		}
		set(env, key, value, ft_strchr(*arr, '='));
	}
	return (g_exit_status);
}

int	unset(t_token *lst, t_env *env)
{
	t_env	*tmp;
	t_env	*prev;

	while (*(++(lst->arr)))
	{
		if (!check_valid_identifier(*(lst->arr)))
		{
			printf("mini: unset: `%s': not a valid identifier\n",
				*(lst->arr));
			g_exit_status = 1;
			continue ;
		}
		tmp = env;
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, *(lst->arr)) && ft_strcmp(tmp->key, "_"))
			{
				if (tmp == env)
				{
					env->next->addr = env->addr;
					env->next->mem = env->mem;
					env->next->pwd = env->pwd;
					env = env->next;
					*(env->addr) = env;
				}
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
		exit(export(lst->arr, env));
	if (!ft_strcmp(lst->arr[0], "unset"))
		exit(unset(lst, env));
	if (!ft_strcmp(lst->arr[0], "exit"))
		exit(exiting(lst, env));
}
