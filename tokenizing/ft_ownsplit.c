#include "../main.h"

void first_ft_word(char *s, char c, t_tokenizer *vars)
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
		while (s[vars->i] != c  && s[vars->i])
			first_ft_word(s, c, vars);
		while (s[vars->i] == c && s[vars->i])
		{
			if (s[vars->i + 1] != c)
				break;
			vars->i++;
		}
		if (!s[vars->i])
			break;
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


char * first_trim(t_tokenizer *trim, char *s)
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
	return s;
}
char *second_trim(t_tokenizer *trim, char *s)
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
	return s;
}
char *third_trim(t_tokenizer *trim, char *s)
{
	trim->arr[trim->k][trim->j++] = *s;
	s++;
	return s;
}
char	**ft_trim(char *s, char c, t_tokenizer *trim)
{
	trim->k = 0;
	while (trim->k < trim->words_count)
	{
		trim->j = 0;
		while (*s == c && *s)
			s++;
		if (*s == '\0')
			break ;
		trim->word_len = ft_len(s, c);
		trim->arr[trim->k] = malloc(sizeof(char) * (trim->word_len + 1));
		if (!trim->arr[trim->k])
			return (NULL);
        while (*s != c && *s)
	    {
			if (*s == '\"')
				s = first_trim(trim, s);
			else if (*s == '\'')
				s = second_trim(trim, s);
			else if (*s != c && *s && *s != '\"' && *s != '\'')
				s = third_trim(trim, s);
	    }
		trim->arr[trim->k++][trim->j] = '\0';
	}
	return (trim->arr);
}
int ft_count_res(int c1, int c2)
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
void ft_count_first(char const *s, t_tokenizer *vars)
{
	vars->count1++;
	vars->i++;
	while (s[vars->i] != '\"' && s[vars->i])
		vars->i++;
	if (s[vars->i] == '\"')
		vars->count1++;
}
void ft_count_second(char const *s, t_tokenizer *vars)
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
		vars->i++;
	}
	if (!ft_count_res(vars->count1, vars->count2))
		return (0);
	return (1);
}
void first_minisplit(char const *s, t_tokenizer *vars)
{
	while (s[vars->i] != '\"' && s[vars->i] != '\''  && s[vars->i])
	{
		vars->res[vars->j++] = s[vars->i];
		vars->i++;
	}
}
void second_minisplit(char const *s, t_tokenizer *vars)
{
	if ((s[vars->i] == '>' && s[vars->i + 1] == '>')
		|| (s[vars->i] == '<' && s[vars->i + 1] == '<'))
	{
		if (s[vars->i - 1] != ' ')
			vars->res[vars->j++] = ' ';
		vars->res[vars->j++] = s[vars->i++];
		vars->res[vars->j++] = s[vars->i];
		if (s[vars->i + 1] != ' ')
			vars->res[vars->j++] = ' ';
	}
	else
	{
		if (s[vars->i - 1] != ' ')
			vars->res[vars->j++] = ' ';
		vars->res[vars->j++] = s[vars->i];
		if (s[vars->i + 1] != ' ')
			vars->res[vars->j++] = ' ';
	}
}
char *minisplit(char const *s, t_tokenizer *vars)
{
	vars->i = 0;
	vars->j = 0;
	vars->res = malloc(sizeof(char) * (ft_strlen(s) * 2));
	if (!vars->res)
		return (NULL);
	while (s[vars->i])
	{
		if (s[vars->i] == '\"' || s[vars->i] == '\'')
		{
			vars->res[vars->j++] = s[vars->i];
			vars->i++;
			first_minisplit(s, vars);
		}
		if (s[vars->i] == '|' || s[vars->i] == '>' || s[vars->i] == '<')
		{
			second_minisplit(s, vars);
			vars->i++;
		}
		vars->res[vars->j++] = s[vars->i];
		vars->i++;
	}
	vars->res[vars->j] = '\0';
	return vars->res;
}
char	**ft_ownsplit(char const *s, char c, t_tokenizer *vars)
{
	t_tokenizer		*trim;
	size_t			words_count;
	char			**arr;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	trim = malloc(sizeof(t_tokenizer));
	if (!trim)
		return NULL;
	s = minisplit(s, vars);
	if (!s)
		return (free(trim), NULL);
	if (!ft_count_quotes(s, vars))	
		return (free(trim), free((char *)s), NULL);
	trim->words_count = ft_word((char *)s, c, vars);
	trim->arr = (char **) malloc(sizeof(char *) * (trim->words_count + 1));
	if (!trim->arr)
		return (free(trim), free((char *)s), NULL);
	trim->arr = ft_trim((char *)s, c, trim);
	if (!trim->arr)
		return (free(trim), free((char *)s) ,NULL);
	trim->arr[trim->words_count] = NULL;
	free((char *)s);
	return (trim->arr);
}
