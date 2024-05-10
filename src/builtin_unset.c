/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:47:56 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:32:39 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_loop(t_env *env, char **arr, t_env *prev, t_env *tmp)
{
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, *arr) && ft_strcmp(tmp->key, "_"))
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

int	unset(t_token *lst, t_env *env)
{
	char	**arr;

	arr = lst->arr;
	while (*++arr)
	{
		if (!check_valid_identifier(*arr))
		{
			printf("mini: unset: `%s': not a valid identifier\n",
				*arr);
			g_exit_status = 1;
			continue ;
		}
		g_exit_status = 0;
		unset_loop(env, arr, NULL, NULL);
	}
	return (g_exit_status);
}
