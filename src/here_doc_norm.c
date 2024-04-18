/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:14:13 by ousabbar          #+#    #+#             */
/*   Updated: 2024/04/18 11:36:17 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	here_doc_expand_norm(t_multx *vars, char *s, t_env *env)
{
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
