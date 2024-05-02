/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ownsplit_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 06:55:32 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/02 06:55:33 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	while (s[vars->i] == c && s[vars->i])
		vars->i++;
	while (s[vars->i])
	{
		vars->count1++;
		while (s[vars->i] != c && s[vars->i])
			first_ft_word(s, vars);
		while (s[vars->i] == c && s[vars->i])
		{
			if (s[vars->i + 1] != c)
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
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			i++;
			while ((s[i] != '\"' || *s == '\'') && s[i])
				i++;
		}
		i++;
	}
	return (i);
}
