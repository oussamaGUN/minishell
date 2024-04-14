#include "../main.h"

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
void ft_delemiter(t_multx *exp_vars, char *s)
{
    exp_vars->res = malloc((ft_strlen(s) + 1) * 1);
    while (s[exp_vars->i])
    {
        if (s[exp_vars->i] != '\'' && s[exp_vars->i] != '\"')
            exp_vars->res[exp_vars->j++] = s[exp_vars->i];
        exp_vars->i++;
    }
    exp_vars->res[exp_vars->j] = '\0';
}
void ft_double_quotes_expand(t_multx *exp_vars, char *s, t_env *env)
{
    exp_vars->i++;
    while (s[exp_vars->i] != '\"' && s[exp_vars->i])
    {
        exp_vars->j = 0;
        if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] == '?')
        {
            exp_vars->i++;
            char *str = ft_itoa(exit_status >> 8);
            exp_vars->res = ft_strjoin(exp_vars->res, str);
            exp_vars->k = ft_strlen(exp_vars->res);
            
        }
        else if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] != ' ' && s[exp_vars->i + 1] != '\'' 
            && s[exp_vars->i + 1] != '\"' && s[exp_vars->i + 1]&& !ft_isdigit(s[exp_vars->i + 1]))
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
                exp_vars->res = ft_strjoin(exp_vars->res, exp_vars->exp);
                exp_vars->k = ft_strlen(exp_vars->res);
            }
            else
                exp_vars->res = ft_strjoin(exp_vars->res, "");
            exp_vars->i--;
        }
        else
        {
            if (s[exp_vars->i] == '$' && ft_isdigit(s[exp_vars->i + 1]))
                exp_vars->i++;
            else
            {
                exp_vars->res = ft_strjoin(exp_vars->res, &s[exp_vars->i]);
            }
        }
        if (exp_vars->res[exp_vars->k])
            exp_vars->k++;
        if (s[exp_vars->i])
            exp_vars->i++;
        exp_vars->res[exp_vars->k] = '\0';
    }
    exp_vars->i++;

}
void ft_single_quotes(t_multx *exp_vars, char *s)
{
    exp_vars->i++;
    while (s[exp_vars->i] != '\'' && s[exp_vars->i])
    {
        exp_vars->res = ft_strjoin(exp_vars->res, &s[exp_vars->i]);
        if (exp_vars->res[exp_vars->k])
            exp_vars->k++;
        if (s[exp_vars->i])
            exp_vars->i++;
        
    }
    exp_vars->i++;
    exp_vars->res[exp_vars->k] = '\0';
}
void ft_exit_value(t_multx *exp_vars, char *s)
{
    exp_vars->i++;
    while (s[exp_vars->i] != '$' && s[exp_vars->i] != ' ' 
        && s[exp_vars->i] != '\"' && s[exp_vars->i] != '\'' && ft_isalnum(s[exp_vars->i]))
        exp_vars->i++;
    char *str = ft_itoa(exit_status >> 8);
    exp_vars->res = ft_strjoin(exp_vars->res, str);
    exp_vars->k = ft_strlen(exp_vars->res);
}
void ft_expand_normalin_multi(t_multx *exp_vars, char *s, t_env *env)
{
    exp_vars->i++;
    while (s[exp_vars->i] != ' ' 
        && s[exp_vars->i] != '\"' && s[exp_vars->i] && ft_isalnum(s[exp_vars->i]))
    {
        exp_vars->inside_dquotes[exp_vars->j] = s[exp_vars->i];
        exp_vars->i++;
        exp_vars->j++;
    }
    exp_vars->inside_dquotes[exp_vars->j] = '\0';
    exp_vars->exp = expand(exp_vars->inside_dquotes, env);
    if (exp_vars->exp)
    {
        exp_vars->res = ft_strjoin(exp_vars->res, exp_vars->exp);
        exp_vars->k = ft_strlen(exp_vars->res);
    }
    else
        exp_vars->res = ft_strjoin(exp_vars->res, "");
    exp_vars->i--;
}
void ft_expand_single_in_multiple(t_multx *exp_vars, char *s)
{
    exp_vars->i++;
    while (s[exp_vars->i] != '\'' && s[exp_vars->i])
    {
        exp_vars->res = ft_strjoin(exp_vars->res, &s[exp_vars->i]);
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
        {
            exp_vars->i++;
            char *str = ft_itoa(exit_status >> 8);
            exp_vars->res = ft_strjoin(exp_vars->res, str);
            exp_vars->k = ft_strlen(exp_vars->res);
            
        }
        else if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] != ' ' && s[exp_vars->i + 1] != '\'' 
            && s[exp_vars->i + 1] != '\"' && s[exp_vars->i + 1]&& !ft_isdigit(s[exp_vars->i + 1]))
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
                exp_vars->res = ft_strjoin(exp_vars->res, exp_vars->exp);
                exp_vars->k = ft_strlen(exp_vars->res);
            }
            else
                exp_vars->res = ft_strjoin(exp_vars->res, "");
            exp_vars->i--;
        }
        else
        {
            if (s[exp_vars->i] == '$' && ft_isdigit(s[exp_vars->i + 1]))
                exp_vars->i++;
            else
            {
                exp_vars->res = ft_strjoin(exp_vars->res, &s[exp_vars->i]);
            }
        }
        if (exp_vars->res[exp_vars->k])
            exp_vars->k++;
        if (s[exp_vars->i])
            exp_vars->i++;
        exp_vars->res[exp_vars->k] = '\0';
    }  
}
void ft_cpying_normal(t_multx *exp_vars, char *s)
{
    if (s[exp_vars->i] == '$' && ft_isdigit(s[exp_vars->i + 1]))
        exp_vars->i++;
    else if (s[exp_vars->i] == '$' && (s[exp_vars->i + 1] == '\"' || s[exp_vars->i + 1] == '\'') && s[exp_vars->i + 2])
        exp_vars->i++;
    else
        exp_vars->res = ft_strjoin(exp_vars->res, &s[exp_vars->i]);
}
void ft_mulitquotes(t_multx *exp_vars, char *s, t_env *env)
{
    while (s[exp_vars->i])
    {
        exp_vars->j = 0;
        if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] == '?')
            ft_exit_value(exp_vars, s);
        else if (s[exp_vars->i] == '$' && s[exp_vars->i + 1] != ' ' && s[exp_vars->i + 1] != '\''
            && s[exp_vars->i + 1] != '\"' && s[exp_vars->i + 1] && !ft_isdigit(s[exp_vars->i + 1]))
            ft_expand_normalin_multi(exp_vars, s, env);
        else if (s[exp_vars->i] == '\'')
            ft_expand_single_in_multiple(exp_vars, s);
        else if (s[exp_vars->i] == '\"')
            ft_expand_double_in_multiple(exp_vars, s, env);
        else
            ft_cpying_normal(exp_vars, s);
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
        ft_delemiter(exp_vars, itter->content);
    else
    {
        exp_vars->res = malloc(1);
        exp_vars->res[0] = '\0';
        while (itter->content[exp_vars->i])
        {
            if (itter->content[exp_vars->i] == '\"')
                ft_double_quotes_expand(exp_vars, itter->content, env);
            else if (itter->content[exp_vars->i] == '\'')
                ft_single_quotes(exp_vars, itter->content);
            else
                ft_mulitquotes(exp_vars, itter->content, env);
        }
    }
}
t_token *expanding(t_token *token, t_env *env)
{
    t_multx *exp_vars = malloc(sizeof(t_multx));
    t_token *itter;

    exp_vars = malloc(sizeof(t_multx));
    if (!exp_vars)
        return NULL;
    exp_vars->inside_dquotes = malloc(ft_strlen(token->content));
    itter = token;
    while (itter)
    {
        exp_vars->i = 0;
        exp_vars->k = 0;
        conditions(exp_vars, itter, env);
        itter->content = ft_strdup(exp_vars->res);
        itter = itter->next;
    }
    
    return token;
}
