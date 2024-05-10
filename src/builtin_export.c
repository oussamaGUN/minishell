/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:52:38 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:16:17 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(t_env *env)
{
	char	*holder;
	bool	visible;
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		while (tmp)
		{
			if (ft_strcmp(env->key, tmp->key) > 0)
			{
				holder = env->key;
				env->key = tmp->key;
				tmp->key = holder;
				holder = env->value;
				env->value = tmp->value;
				tmp->value = holder;
				visible = env->visible;
				env->visible = tmp->visible;
				tmp->visible = visible;
			}
			tmp = tmp->next;
		}
		env = env->next;
	}
}

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

int	set(t_env	*env, char *key, char *value, bool visible)
{
	t_env	*tmp;
	t_env	*new;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = value;
			tmp->visible = visible;
			return (free(key), 0);
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->key = key;
	new->value = value;
	new->visible = visible;
	new->next = env->next;
	env->next = new;
	return (0);
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
