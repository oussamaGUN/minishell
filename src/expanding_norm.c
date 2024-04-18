/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_norm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:13:46 by ousabbar          #+#    #+#             */
/*   Updated: 2024/04/18 10:36:35 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_expanding_the_inside(t_multx *exp_vars, char *s, t_env *env)
{
	exp_vars->i++;
	while (s[exp_vars->i] != '$' && s[exp_vars->i] != ' '
		&& s[exp_vars->i] != '\"' && ft_isalnum(s[exp_vars->i]))
	{
		exp_vars->inside_dquotes[exp_vars->j] = s[exp_vars->i];
		exp_vars->i++;
		exp_vars->j++;
	}
	exp_vars->inside_dquotes[exp_vars->j] = '\0';
	exp_vars->exp = expand(exp_vars->inside_dquotes, env);
	if (exp_vars->exp)
	{
		exp_vars->res = ft_malloc(0, &(env->mem),
				ft_strjoin(exp_vars->res, exp_vars->exp));
		exp_vars->k = ft_strlen(exp_vars->res);
	}
	else
		exp_vars->res = ft_malloc(0, &(env->mem),
				ft_strjoin(exp_vars->res, ""));
	exp_vars->i--;
}

void	ft_double_quotes_expand(t_multx *exp_vars, char *s, t_env *env)
{
	exp_vars->i++;
	while (s[exp_vars->i] != '\"' && s[exp_vars->i])
	{
		exp_vars->j = 0;
		if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] == '?')
			ft_exit_value(exp_vars, s, env);
		else if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] != ' '
			&& s[exp_vars->i + 1] != '\'' && s[exp_vars->i + 1] != '\"'
			&& s[exp_vars->i + 1] && !ft_isdigit(s[exp_vars->i + 1]))
			ft_expanding_the_inside(exp_vars, s, env);
		else
		{
			if (s[exp_vars->i] == '$' && ft_isdigit(s[exp_vars->i + 1]))
				exp_vars->i++;
			else
				exp_vars->res = ft_malloc(0, &(env->mem),
						ft_strjoin(exp_vars->res, &s[exp_vars->i]));
		}
		if (exp_vars->res[exp_vars->k])
			exp_vars->k++;
		if (s[exp_vars->i])
			exp_vars->i++;
		exp_vars->res[exp_vars->k] = '\0';
	}
	exp_vars->i++;
}

void	ft_single_quotes(t_multx *exp_vars, char *s, t_env *env)
{
	exp_vars->i++;
	while (s[exp_vars->i] != '\'' && s[exp_vars->i])
	{
		exp_vars->res = ft_malloc(0, &(env->mem),
				ft_strjoin(exp_vars->res, &s[exp_vars->i]));
		if (exp_vars->res[exp_vars->k])
			exp_vars->k++;
		if (s[exp_vars->i])
			exp_vars->i++;
	}
	exp_vars->i++;
	exp_vars->res[exp_vars->k] = '\0';
}

void	ft_expand_normalin_multi(t_multx *exp_vars, char *s, t_env *env)
{
	exp_vars->i++;
	while (s[exp_vars->i] != ' '
		&& s[exp_vars->i] != '\"' && s[exp_vars->i] != '\''
		&& s[exp_vars->i] && ft_isalnum(s[exp_vars->i]))
	{
		exp_vars->inside_dquotes[exp_vars->j] = s[exp_vars->i];
		exp_vars->i++;
		exp_vars->j++;
	}
	exp_vars->inside_dquotes[exp_vars->j] = '\0';
	exp_vars->exp = expand(exp_vars->inside_dquotes, env);
	if (exp_vars->exp)
	{
		exp_vars->res = ft_malloc(0, &(env->mem),
				ft_strjoin(exp_vars->res, exp_vars->exp));
		exp_vars->k = ft_strlen(exp_vars->res);
	}
	else
		exp_vars->res = ft_malloc(0, &(env->mem),
				ft_strjoin(exp_vars->res, ""));
	exp_vars->i--;
}

void	ft_expand_single_in_multiple(t_multx *exp_vars, char *s, t_env *env)
{
	exp_vars->i++;
	while (s[exp_vars->i] != '\'' && s[exp_vars->i])
	{
		exp_vars->res = ft_malloc(0, &(env->mem),
				ft_strjoin(exp_vars->res, &s[exp_vars->i]));
		if (exp_vars->res[exp_vars->k])
			exp_vars->k++;
		if (s[exp_vars->i])
			exp_vars->i++;
	}
	exp_vars->res[exp_vars->k] = '\0';
}
