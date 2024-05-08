/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:05:04 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/08 09:14:03 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	print_sorted_export(t_env *env)
{
	sort_env(env);
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
	return (0);
}

bool	export_spliting(char **arr, char **key, char **value)
{
	char	**sp;

	sp = ft_split(*arr, '=');
	if (!sp[0])
	{
		printf("mini: export: `%s': not a valid identifier\n",
			*arr);
		g_exit_status = 1;
		free(sp);
		return (false);
	}
	*key = sp[0];
	if (!sp[1])
		*value = ft_strdup("");
	else
		*value = sp[1];
	free(sp);
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
		if (!export_spliting(arr, &key, &value))
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
		set(env, key, value);
	}
	return (g_exit_status);
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
			if (!ft_strcmp(tmp->key, *(lst->arr)) && ft_strcmp(tmp->key, "_"))
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
		exit(export(lst->arr, env));
	if (!ft_strcmp(lst->arr[0], "unset"))
		exit(unset(lst, env));
	if (!ft_strcmp(lst->arr[0], "exit"))
		exit(exiting(lst, env));
}
