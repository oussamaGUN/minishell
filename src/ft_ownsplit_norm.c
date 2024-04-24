#include "main.h"

void	first_minisplit(char const *s, t_tokenizer *vars)
{
	vars->res[vars->j++] = s[vars->i++];
	while (s[vars->i] != '\"' && s[vars->i] != '\'' && s[vars->i])
		vars->res[vars->j++] = s[vars->i++];
	vars->res[vars->j++] = s[vars->i++];
}

void	second_minisplit(char const *s, t_tokenizer *vars)
{
	if ((s[vars->i] == '>' && s[vars->i + 1] == '>')
		|| (s[vars->i] == '<' && s[vars->i + 1] == '<'))
	{
		if (vars->i - 1 > 0)
			if (s[vars->i - 1] != ' ')
				vars->res[vars->j++] = ' ';
		vars->res[vars->j++] = s[vars->i++];
		vars->res[vars->j++] = s[vars->i];
		if (s[vars->i + 1] != ' ')
			vars->res[vars->j++] = ' ';
	}
	else
	{
		// printf("addr s={%p}\n",s);
		// printf("addr var->res={%p}\n",vars->res);
		if (vars->i - 1 > 0)
			if (s[vars->i - 1] != ' ')
				vars->res[vars->j++] = ' ';
		vars->res[vars->j++] = s[vars->i];
		if (s[vars->i + 1] != ' ')
			vars->res[vars->j++] = ' ';
	}
}

char	*minisplit(char const *s, t_tokenizer *vars)
{
	vars->i = 0;
	vars->j = 0;
	vars->res = malloc(sizeof(char) * (ft_strlen(s) * 2));
	if (!vars->res)
		return (NULL);
	while (s[vars->i])
	{
		if (s[vars->i] == '\"' || s[vars->i] == '\'')
			first_minisplit(s, vars);
		else if (s[vars->i] == '|' || s[vars->i] == '>' || s[vars->i] == '<')
		{
			second_minisplit(s, vars);
			vars->i++;
		}
		else
			vars->res[vars->j++] = s[vars->i++];
	}
	vars->res[vars->j] = '\0';
	return (vars->res);
}
