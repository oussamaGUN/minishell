/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:57:38 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:16:17 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exiting(t_token *lst, t_env *env)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (lst->arr[1])
	{
		if (lst->arr[1][0] == '-' || lst->arr[1][0] == '+')
			i++;
		while (lst->arr[1][i])
		{
			if (!ft_isdigit(lst->arr[1][i++]))
			{
				printf("mini: exit: %s: numeric argument required\n",
					lst->arr[1]);
				env_clear(&env);
				exit(255);
			}
		}
		if (lst->arr[2])
			return (printf("mini: exit: too many arguments\n"), 1);
		g_exit_status = ft_atoi(lst->arr[1]);
	}
	env_clear(&env);
	exit(g_exit_status % 256);
}
