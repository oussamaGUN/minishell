/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ownsplit_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 06:54:40 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:16:17 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_res(int c1, int c2)
{
	if (c1 % 2 == 1)
	{
		ft_putendl_fd("missing double quotes", 2);
		return (0);
	}
	if (c2 % 2 == 1)
	{
		ft_putendl_fd("missing single quotes", 2);
		return (0);
	}
	return (1);
}

void	ft_count_first(char const *s, t_tokenizer *vars)
{
	vars->count1++;
	vars->i++;
	while (s[vars->i] != '\"' && s[vars->i])
		vars->i++;
	if (s[vars->i] == '\"')
		vars->count1++;
}

void	ft_count_second(char const *s, t_tokenizer *vars)
{
	vars->count2++;
	vars->i++;
	while (s[vars->i] != '\'' && s[vars->i])
		vars->i++;
	if (s[vars->i] == '\'')
		vars->count2++;
}

int	ft_count_quotes(char const *s, t_tokenizer *vars)
{
	vars->count1 = 0;
	vars->count2 = 0;
	vars->i = 0;
	while (s[vars->i])
	{
		if (s[vars->i] == '\"')
			ft_count_first(s, vars);
		else if (s[vars->i] == '\'')
			ft_count_second(s, vars);
		if (s[vars->i])
			vars->i++;
	}
	if (!ft_count_res(vars->count1, vars->count2))
		return (0);
	return (1);
}
