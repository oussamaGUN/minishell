/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ownsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 06:54:20 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:16:17 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*first_trim(t_tokenizer *trim, char *s)
{
	if (*s == '\"')
		trim->arr[trim->k][trim->j++] = '\"';
	s++;
	while (*s != '\"' && *s)
	{
		trim->arr[trim->k][trim->j++] = *s;
		s++;
	}
	if (*s == '\"')
		trim->arr[trim->k][trim->j++] = '\"';
	if (*s)
		s++;
	return (s);
}

char	*second_trim(t_tokenizer *trim, char *s)
{
	if (*s == '\'')
		trim->arr[trim->k][trim->j++] = '\'';
	s++;
	while (*s != '\'' && *s)
	{
		trim->arr[trim->k][trim->j++] = *s;
		s++;
	}
	if (*s == '\'')
		trim->arr[trim->k][trim->j++] = '\'';
	if (*s)
		s++;
	return (s);
}

char	*third_trim(t_tokenizer *trim, char *s)
{
	trim->arr[trim->k][trim->j++] = *s;
	s++;
	return (s);
}

char	**ft_trim(char *s, char c, t_tokenizer *trim, t_free **mem)
{
	trim->k = 0;
	while (trim->k < trim->words_count)
	{
		trim->j = 0;
		while ((*s == c || *s == '\t') && *s)
			s++;
		if (*s == '\0')
			break ;
		trim->word_len = ft_len(s, c);
		trim->arr[trim->k] = ft_malloc(sizeof(char) * (trim->word_len + 1),
				mem, NULL);
		if (!trim->arr[trim->k])
			return (NULL);
		while (*s != c && *s != '\t' && *s)
		{
			if (*s == '\"')
				s = first_trim(trim, s);
			else if (*s == '\'')
				s = second_trim(trim, s);
			else if (*s != c && *s != '\t' && *s && *s != '\"' && *s != '\'')
				s = third_trim(trim, s);
		}
		trim->arr[trim->k++][trim->j] = '\0';
	}
	return (trim->arr);
}

char	**ft_ownsplit(char const *s, char c, t_tokenizer *vars, t_free **mem)
{
	t_tokenizer		*trim;

	trim = ft_malloc(sizeof(t_tokenizer), mem, NULL);
	if (!trim)
		return (NULL);
	if (!ft_count_quotes(s, vars))
		return (NULL);
	s = minisplit(s, vars);
	if (!s)
		return (NULL);
	trim->words_count = ft_word((char *)s, c, vars);
	trim->arr = (char **) ft_malloc(sizeof(char *) * (trim->words_count + 1),
			mem, NULL);
	if (!trim->arr)
		return (free((char *)s), NULL);
	trim->arr = ft_trim((char *)s, c, trim, mem);
	if (!trim->arr)
		return (free((char *)s), NULL);
	trim->arr[trim->words_count] = NULL;
	free((char *)s);
	return (trim->arr);
}
