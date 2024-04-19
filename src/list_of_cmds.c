/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_of_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:54:54 by ousabbar          #+#    #+#             */
/*   Updated: 2024/04/19 08:09:44 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_token	*ft_list(t_token *token, t_env *env)
{
	t_token	*lst;
	t_token	*node;
	t_multx	*vars;
	static int	status;

	vars = ft_malloc(sizeof(t_multx), &(env->mem), NULL);
	if (!vars)
		return (NULL);
	lst = NULL;
	while (token)
	{
		node = add_token(NULL, &(env->mem));
		node->exit_status = 0;
		if (!norm1(node, vars, token, &(env->mem)))
			return (NULL);
		while (token && token->type != PIPE)
		{
			if (!norm2(token, env, node, vars))
				return (NULL);
			if (node->exit_status == 1)
				status = 1;
			token = token->next;
		}
		node->exit_status = status;
		status = 0;
		node->arr[vars->i] = NULL;
		ft_lstadd(&lst, node);
		if (token)
			token = token->next;
	}
	return (lst);
}
