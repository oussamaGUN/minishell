/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_of_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:54:54 by ousabbar          #+#    #+#             */
/*   Updated: 2024/04/22 10:22:28 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_token	*ft_list_loop(t_token *token, t_env *env, t_token *node, t_multx *vars)
{
	while (token && token->type != PIPE)
	{
		if (!norm2(token, env, node, vars))
			return (NULL);
		token = token->next;
	}
	return (token);
}

t_token	*ft_list(t_token *token, t_env *env)
{
	t_token	*lst;
	t_token	*node;
	t_multx	*vars;

	vars = (t_multx *)ft_malloc(sizeof(t_multx), &(env->mem), NULL);
	if (!vars)
		return (NULL);
	lst = NULL;
	while (token)
	{
		node = add_token(NULL, &(env->mem));
		if (!init(node, vars, token, &(env->mem)))
			return (NULL);
		token = ft_list_loop(token, env, node, vars);
		node->exit_status = node->status;
		node->arr[vars->i] = NULL;
		node->status = 0;
		ft_lstadd(&lst, node);
		if (token)
			token = token->next;
	}
	return (lst);
}
