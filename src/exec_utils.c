/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:00:50 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/07 11:18:04 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	**env_to_arr(t_env *env)
{
	t_env	*tmp;
	char	**arr;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	arr = ft_malloc(sizeof(char *) * (i + 1), &(env->mem), NULL);
	if (!arr)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		arr[i] = ft_malloc(0, &(env->mem), ft_strjoin(tmp->key, "="));
		arr[i] = ft_malloc(0, &(env->mem), ft_strjoin(arr[i], tmp->value));
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	close_fds(t_token *lst)
{
	while (lst)
	{
		if (lst->next)
		{
			close(lst->fd[STDIN_FILENO]);
			close(lst->fd[STDOUT_FILENO]);
		}
		lst = lst->next;
	}
}
