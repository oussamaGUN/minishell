#include "main.h"

char *expand(char *s, t_env *envp)
{
	t_env *lst = envp;
	while (lst)
	{
		if (ft_strncmp(lst->key, s, ft_strlen(s)) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return NULL;
}
void ft_exit_value(t_multx *exp_vars, char *s, t_env *env)
{
	exp_vars->i++;
	exp_vars->res = ft_malloc(0, &(env->mem), ft_strjoin(exp_vars->res,
					ft_malloc(0, &(env->mem), ft_itoa(exit_status >> 8))));
	exp_vars->k = ft_strlen(exp_vars->res);
}
void ft_delemiter(t_multx *exp_vars, char *s, t_free **mem)
{
	exp_vars->res = ft_malloc((ft_strlen(s) + 1) * 1, mem, NULL);
	if (!exp_vars->res)
		return ;
	while (s[exp_vars->i])
	{
		if (s[exp_vars->i] != '\'' && s[exp_vars->i] != '\"')
			exp_vars->res[exp_vars->j++] = s[exp_vars->i];
		exp_vars->i++;
	}
	exp_vars->res[exp_vars->j] = '\0';
}
void ft_expanding_the_inside(t_multx *exp_vars, char *s, t_env *env)
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
void ft_double_quotes_expand(t_multx *exp_vars, char *s, t_env *env)
{
	exp_vars->i++;
	while (s[exp_vars->i] != '\"' && s[exp_vars->i])
	{
		exp_vars->j = 0;
		if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] == '?')
			ft_exit_value(exp_vars, s, env);
		else if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] != ' ' && s[exp_vars->i + 1] != '\'' 
			&& s[exp_vars->i + 1] != '\"' && s[exp_vars->i + 1] && !ft_isdigit(s[exp_vars->i + 1]))
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
void ft_single_quotes(t_multx *exp_vars, char *s, t_env *env)
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

void ft_expand_normalin_multi(t_multx *exp_vars, char *s, t_env *env)
{
	exp_vars->i++;
	while (s[exp_vars->i] != ' ' 
		&& s[exp_vars->i] != '\"' && s[exp_vars->i] != '\'' && s[exp_vars->i] && ft_isalnum(s[exp_vars->i]))
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
void ft_expand_single_in_multiple(t_multx *exp_vars, char *s, t_env *env)
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
void ft_expand_double_in_multiple(t_multx *exp_vars, char *s, t_env *env)
{
	exp_vars->i++;
	while (s[exp_vars->i] != '\"' && s[exp_vars->i])
	{
		exp_vars->j = 0;
		if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] == '?')
			ft_exit_value(exp_vars, s, env);
		else if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] != ' ' && s[exp_vars->i + 1] != '\'' 
			&& s[exp_vars->i + 1] != '\"' && s[exp_vars->i + 1] && !ft_isdigit(s[exp_vars->i + 1]))
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
void ft_cpying_normal(t_multx *exp_vars, char *s, t_env *env)
{
	if (s[exp_vars->i] == '$' && ft_isdigit(s[exp_vars->i + 1]))
		exp_vars->i++;
	else if (s[exp_vars->i] == '$' && (s[exp_vars->i + 1] == '\"' || s[exp_vars->i + 1] == '\'') && s[exp_vars->i + 2])
		exp_vars->i++;
	else
		exp_vars->res = ft_malloc(0, &(env->mem),
						ft_strjoin(exp_vars->res, &s[exp_vars->i]));
}
void ft_mulitquotes(t_multx *exp_vars, char *s, t_env *env)
{
	while (s[exp_vars->i])
	{
		exp_vars->j = 0;
		if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] == '?')
			ft_exit_value(exp_vars, s, env);
		else if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] != ' ' && s[exp_vars->i + 1] != '\''
			&& s[exp_vars->i + 1] != '\"' && s[exp_vars->i + 1] && !ft_isdigit(s[exp_vars->i + 1]))
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
void conditions(t_multx *exp_vars, t_token *itter, t_env *env)
{
	if (itter->type == DELIMITER)
		ft_delemiter(exp_vars, itter->content, &(env->mem));
	else
	{
		exp_vars->res = ft_malloc(1, &(env->mem), NULL);
		exp_vars->res[0] = '\0';
		while (itter->content[exp_vars->i]) 
		{
			if (itter->content[exp_vars->i] == '\"')
				ft_double_quotes_expand(exp_vars, itter->content, env);
			else if (itter->content[exp_vars->i] == '\'')
				ft_single_quotes(exp_vars, itter->content, env);
			else
				ft_mulitquotes(exp_vars, itter->content, env);
		}
	}
}
t_token *expanding(t_token *token, t_env *env)
{
	t_multx	*exp_vars;
	t_token	*itter;

	exp_vars = ft_malloc(sizeof(t_multx), &(env->mem), NULL);
	if (!exp_vars)
		return (NULL);
	exp_vars->inside_dquotes = ft_malloc(ft_strlen(token->content), &(env->mem), NULL);
	if (!exp_vars)
		return (NULL);
	itter = token;
	while (itter)
	{
		exp_vars->i = 0;
		exp_vars->k = 0;
		conditions(exp_vars, itter, env);
		itter->content = ft_malloc(0 , &(env->mem), ft_strdup(exp_vars->res));
		itter = itter->next;
	}
	
	return token;
}