/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_of_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:54:54 by ousabbar          #+#    #+#             */
/*   Updated: 2024/04/18 11:13:13 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_token	*ft_list(t_token *token, t_env *env)
{
	t_token	*lst;
	t_token	*node;
	t_multx	*vars;

	vars = ft_malloc(sizeof(t_multx), &(env->mem), NULL);
	if (!vars)
		return (NULL);
	lst = NULL;
	while (token)
	{
		node = add_token(NULL, &(env->mem));
		if (!norm1(node, vars, token, &(env->mem)))
			return (NULL);
		while (token && token->type != PIPE)
		{
			if (!norm2(token, env, node, vars))
				return (NULL);
			token = token->next;
		}
		node->arr[vars->i] = NULL;
		ft_lstadd(&lst, node);
		if (token)
			token = token->next;
	}
	return (lst);
}
