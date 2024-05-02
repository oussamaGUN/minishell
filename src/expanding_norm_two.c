/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_norm_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 06:47:10 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/02 11:11:02 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*expand(char *s, t_env *envp)
{
	t_env	*lst;

	lst = envp;
	while (lst)
	{
		if (ft_strncmp(lst->key, s, ft_strlen(s)) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_exit_value(t_multx *exp_vars, t_env *env)
{
	exp_vars->i++;
	exp_vars->res = ft_malloc(0, &(env->mem), ft_strjoin(exp_vars->res,
				ft_malloc(0, &(env->mem), ft_itoa(g_exit_status))));
	exp_vars->k = ft_strlen(exp_vars->res);
}

void	ft_delemiter(t_multx *exp_vars, t_token *itter, t_free **mem)
{
	if (ft_strchr(itter->content, '\'') || ft_strchr(itter->content, '\"'))
		itter->here_doc_check = 0;
	exp_vars->res = ft_malloc((ft_strlen(itter->content) + 1) * 1, mem, NULL);
	if (!exp_vars->res)
		return ;
	while (itter->content[exp_vars->i])
	{
		if (itter->content[exp_vars->i] != '\''
			&& itter->content[exp_vars->i] != '\"')
			exp_vars->res[exp_vars->j++] = itter->content[exp_vars->i];
		exp_vars->i++;
	}
	exp_vars->res[exp_vars->j] = '\0';
}
