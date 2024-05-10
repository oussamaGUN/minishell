/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:03:50 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:22:36 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(t_env *env)
{
	while (env)
	{
		if (env->visible)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

t_env	*ft_update_pwd_env(t_env *env)
{
	char	*cwd;
	char	tmp[4096];
	t_env	*p_env;

	cwd = getcwd(tmp, 4096);
	cwd = strdup(tmp);
	if (!cwd)
		cwd = ft_strdup(env->pwd);
	if (env->pwd)
		free(env->pwd);
	env->pwd = ft_strdup(cwd);
	p_env = env;
	while (p_env)
	{
		if (!ft_strcmp(p_env->key, "PWD"))
		{
			if (p_env->value != cwd)
				free(p_env->value);
			return (p_env->value = cwd, env);
		}
		p_env = p_env->next;
	}
	set(env, ft_strdup("PWD"), cwd, true);
	return (env);
}

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

t_env	*ft_update_underscore(t_env *env, t_token *cmd_list)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "_"))
		{
			if (tmp->value)
				free(tmp->value);
			if (arr_len(cmd_list->arr) > 0 && !cmd_list->next)
				tmp->value = ft_strdup(ft_getpathfor_underscore(
							cmd_list->arr[arr_len(cmd_list->arr) - 1], env));
			else
				tmp->value = ft_strdup("");
			break ;
		}
		tmp = tmp->next;
	}
	return (env);
}
