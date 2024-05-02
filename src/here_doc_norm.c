/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 06:56:02 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/02 06:56:15 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	here_doc_expand_norm(t_multx *vars, char *s, t_env *env)
{
	if (s[vars->i] == '$' && s[vars->i + 1] == '?')
	{
		ft_exit_value(vars, env);
		return ;
	}
	vars->i++;
	while (s[vars->i] != ' '
		&& s[vars->i] && ft_isalnum(s[vars->i]))
	{
		vars->inside_dquotes[vars->j] = s[vars->i];
		vars->i++;
		vars->j++;
	}
	vars->inside_dquotes[vars->j] = '\0';
	vars->exp = expand(vars->inside_dquotes, env);
	if (vars->exp)
	{
		vars->res = ft_malloc(0, &(env->mem),
				ft_strjoin(vars->res, vars->exp));
		vars->k = ft_strlen(vars->res);
	}
	else
		vars->res = ft_malloc(0, &(env->mem), ft_strjoin(vars->res, ""));
	vars->i--;
}

void	here_doc_expand_norm_two(t_multx *vars, char *s, t_env *env)
{
	if (s[vars->i] == '$' && ft_isdigit(s[vars->i + 1]))
		vars->i++;
	else
		vars->res = ft_malloc(0, &(env->mem),
				ft_strjoin(vars->res, &s[vars->i]));
}
