/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ownsplit_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 06:55:32 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 16:56:36 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_ft_word(char *s, t_tokenizer *vars)
{
	if (s[vars->i] == '\"')
	{
		vars->i++;
		while (s[vars->i] != '\"' && s[vars->i])
			vars->i++;
	}
	else if (s[vars->i] == '\'')
	{
		vars->i++;
		while (s[vars->i] != '\'' && s[vars->i])
			vars->i++;
	}
	vars->i++;
}

int	ft_word(char *s, char c, t_tokenizer *vars)
{
	vars->count1 = 0;
	vars->i = 0;
	while ((s[vars->i] == c || s[vars->i] == '\t') && s[vars->i])
		vars->i++;
	while (s[vars->i])
	{
		vars->count1++;
		while (s[vars->i] != c && s[vars->i] != '\t' && s[vars->i])
			first_ft_word(s, vars);
		while ((s[vars->i] == c || s[vars->i] == '\t') && s[vars->i])
		{
			if (s[vars->i + 1] != c && s[vars->i + 1] != '\t')
				break ;
			vars->i++;
		}
		if (!s[vars->i])
			break ;
		vars->i++;
	}
	return (vars->count1);
}

int	ft_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c && s[i] != '\t')
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			i++;
			while (s[i] != '\"' && s[i] != '\'' && s[i])
				i++;
		}
		i++;
	}
	return (i);
}
