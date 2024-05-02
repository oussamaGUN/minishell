/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:16:46 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/02 18:56:45 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	reset_io(t_token *lst)
{
	dup2(lst->fd[0], STDIN_FILENO);
	dup2(lst->fd[1], STDOUT_FILENO);
	close(lst->fd[0]);
	close(lst->fd[1]);
	return (0);
}

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

int	single_builtins(t_token *lst, t_env *env)
{
	lst->fd[0] = dup(STDIN_FILENO);
	lst->fd[1] = dup(STDOUT_FILENO);
	if (set_io(lst))
		return (reset_io(lst), 1);
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
		return (exiting(lst, env));
	return (reset_io(lst), (-2));
}
