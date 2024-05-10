/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_norm_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 06:47:10 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:16:17 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char *s, t_env *envp)
{
	t_env	*lst;

	lst = envp;
	while (lst)
	{
		if (ft_strcmp(lst->key, s) == 0)
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
