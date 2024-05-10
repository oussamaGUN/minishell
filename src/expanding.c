/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 06:46:34 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:16:17 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_double_in_multiple(t_multx *exp_vars, char *s, t_env *env)
{
	exp_vars->i++;
	exp_vars->quotes = true;
	while (s[exp_vars->i] != '\"' && s[exp_vars->i])
	{
		exp_vars->j = 0;
		if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] == '?')
			ft_exit_value(exp_vars, env);
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
}

void	ft_cpying_normal(t_multx *exp_vars, char *s, t_env *env)
{
	if (s[exp_vars->i] == '$' && (s[exp_vars->i + 1] == '\"'
			|| s[exp_vars->i + 1] == '\'') && s[exp_vars->i + 2])
	{
		if (s[exp_vars->i + 1] != '\'')
			exp_vars->i++;
	}
	else if (s[exp_vars->i] == '$' && ft_isdigit(s[exp_vars->i + 1]))
		exp_vars->i++;
	else
		exp_vars->res = ft_malloc(0, &(env->mem),
				ft_strjoin(exp_vars->res, &s[exp_vars->i]));
}

void	ft_mulitquotes(t_multx *exp_vars, char *s, t_env *env)
{
	while (s[exp_vars->i])
	{
		exp_vars->j = 0;
		if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] == '?')
			ft_exit_value(exp_vars, env);
		else if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] != ' '
			&& s[exp_vars->i + 1] != '\'' && s[exp_vars->i + 1] != '\"'
			&& s[exp_vars->i + 1] && !ft_isdigit(s[exp_vars->i + 1]))
			ft_expand_normalin_multi(exp_vars, s, env);
		else if (s[exp_vars->i] == '\'')
			ft_expand_single_in_multiple(exp_vars, s, env);
		else if (s[exp_vars->i] == '\"')
			ft_expand_double_in_multiple(exp_vars, s, env);
		else
			ft_cpying_normal(exp_vars, s, env);
		if (exp_vars->res[exp_vars->k])
			exp_vars->k++;
		if (s[exp_vars->i])
			exp_vars->i++;
		exp_vars->res[exp_vars->k] = '\0';
	}
	if ((s[exp_vars->i] == '\'' || s[exp_vars->i]) && s[exp_vars->i])
		exp_vars->i++;
}

void	conditions(t_multx *exp_vars, t_token *itter, t_env *env)
{
	exp_vars->i = 0;
	exp_vars->k = 0;
	if (itter->type == DELIMITER)
		ft_delemiter(exp_vars, itter, &(env->mem));
	else
	{
		exp_vars->res = ft_malloc(1, &(env->mem), NULL);
		exp_vars->res[0] = '\0';
		while (itter->content[exp_vars->i])
		{
			if (itter->content[exp_vars->i] == '\"')
			{
				exp_vars->quotes = true;
				ft_double_quotes_expand(exp_vars, itter->content, env);
			}
			else if (itter->content[exp_vars->i] == '\'')
				ft_single_quotes(exp_vars, itter->content, env);
			else
				ft_mulitquotes(exp_vars, itter->content, env);
		}
	}
}

t_token	*expanding(t_token *token, t_env *env)
{
	t_multx	*exp_vars;
	t_token	*itter;

	exp_vars = (t_multx *)ft_malloc(sizeof(t_multx), &(env->mem), NULL);
	if (!exp_vars)
		return (NULL);
	itter = token;
	while (itter)
	{
		exp_vars->quotes = false;
		exp_vars->inside_dquotes = ft_malloc(ft_strlen(itter->content),
				&(env->mem), NULL);
		if (!exp_vars)
			return (NULL);
		conditions(exp_vars, itter, env);
		if (!ft_strlen(exp_vars->res) && !(exp_vars->quotes))
			itter->execute = false;
		else
			itter->execute = true;
		itter->content = ft_malloc(0, &(env->mem), ft_strdup(exp_vars->res));
		itter = itter->next;
	}
	return (token);
}
