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
t_token *expanding(t_token *token, t_env *env)
{
    t_multx *exp_vars = malloc(sizeof(t_multx));
    exp_vars->k = 0;
    exp_vars->j = 0;
    exp_vars->inside_dquotes = malloc(ft_strlen(token->content));
    t_token *itter = token;


    while (itter)
    {
        exp_vars->i = 0;
        exp_vars->k = 0;
        if (itter->type == DELIMITER)
        {
            exp_vars->res = malloc((ft_strlen(itter->content) + 1) * 1);
            while (itter->content[exp_vars->i])
            {
                if (itter->content[exp_vars->i] != '\'' && itter->content[exp_vars->i] != '\"')
                    exp_vars->res[exp_vars->j++] = itter->content[exp_vars->i];
                exp_vars->i++;
            }
            exp_vars->res[exp_vars->j] = '\0';
        }
        else
        {
            exp_vars->res = malloc(1);
            exp_vars->res[0] = '\0';
            while (itter->content[exp_vars->i])
            {
                if (itter->content[exp_vars->i] == '\"')
                {
                    exp_vars->i++;
                    while (itter->content[exp_vars->i] != '\"' && itter->content[exp_vars->i])
                    {
                        exp_vars->j = 0;
                        if (itter->content[exp_vars->i] == '$' && itter->content[exp_vars->i + 1] == '?')
                        {
                            exp_vars->i++;
                            char *str = ft_itoa(exit_status >> 8);
                            exp_vars->res = ft_strjoin(exp_vars->res, str);
                            exp_vars->k = ft_strlen(exp_vars->res);
                            
                        }
                        else if (itter->content[exp_vars->i] == '$' && itter->content[exp_vars->i + 1] != ' ' && itter->content[exp_vars->i + 1] != '\'' 
                            && itter->content[exp_vars->i + 1] != '\"' && itter->content[exp_vars->i + 1]&& !ft_isdigit(itter->content[exp_vars->i + 1]))
                        {
                            exp_vars->i++;
                            while (itter->content[exp_vars->i] != '$' && itter->content[exp_vars->i] != ' ' 
                                && itter->content[exp_vars->i] != '\"' && ft_isalnum(itter->content[exp_vars->i]))
                            {
                                exp_vars->inside_dquotes[exp_vars->j] = itter->content[exp_vars->i];
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
                            if (itter->content[exp_vars->i] == '$' && ft_isdigit(itter->content[exp_vars->i + 1]))
                                exp_vars->i++;
                            else
                            {
    
                                exp_vars->res = ft_strjoin(exp_vars->res, &itter->content[exp_vars->i]);
                            }
                        }
                        if (exp_vars->res[exp_vars->k])
                            exp_vars->k++;
                        if (itter->content[exp_vars->i])
                            exp_vars->i++;
                        exp_vars->res[exp_vars->k] = '\0';
                    }
                    exp_vars->i++;

                }
                else if (itter->content[exp_vars->i] == '\'')
                {
                    exp_vars->i++;
                    while (itter->content[exp_vars->i] != '\'' && itter->content[exp_vars->i])
                    {
                        exp_vars->res = ft_strjoin(exp_vars->res, &itter->content[exp_vars->i]);
                        if (exp_vars->res[exp_vars->k])
                            exp_vars->k++;
                        if (itter->content[exp_vars->i])
                            exp_vars->i++;
                        
                    }
                    exp_vars->i++;
                    exp_vars->res[exp_vars->k] = '\0';
                }
                else
                {
                    while (itter->content[exp_vars->i] != '\"' && itter->content[exp_vars->i] != '\'' && itter->content[exp_vars->i])
                    {
                        exp_vars->j = 0;
                        if (itter->content[exp_vars->i] == '$' && itter->content[exp_vars->i + 1] == '?')
                        {
                            exp_vars->i++;
                            while (itter->content[exp_vars->i] != '$' && itter->content[exp_vars->i] != ' ' 
                                && itter->content[exp_vars->i] != '\"' && itter->content[exp_vars->i] != '\'' && ft_isalnum(itter->content[exp_vars->i]))
                                exp_vars->i++;
                            char *str = ft_itoa(exit_status >> 8);
                            exp_vars->res = ft_strjoin(exp_vars->res, str);
                            exp_vars->k = ft_strlen(exp_vars->res);
                        }
                        else if (itter->content[exp_vars->i] == '$' && itter->content[exp_vars->i + 1] != ' ' && itter->content[exp_vars->i + 1] != '\''
                            && itter->content[exp_vars->i + 1] != '\"' && itter->content[exp_vars->i + 1] && !ft_isdigit(itter->content[exp_vars->i + 1]))
                        {
                            exp_vars->i++;
                            while (itter->content[exp_vars->i] != ' ' 
                                && itter->content[exp_vars->i] != '\"' && itter->content[exp_vars->i] && ft_isalnum(itter->content[exp_vars->i]))
                            {
                                exp_vars->inside_dquotes[exp_vars->j] = itter->content[exp_vars->i];
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
                        else if (itter->content[exp_vars->i] == '\'')
                        {
                            exp_vars->i++;
                            while (itter->content[exp_vars->i] != '\'' && itter->content[exp_vars->i])
                            {
                                exp_vars->res = ft_strjoin(exp_vars->res, &itter->content[exp_vars->i]);
                                if (exp_vars->res[exp_vars->k])
                                    exp_vars->k++;
                                if (itter->content[exp_vars->i])
                                    exp_vars->i++;
                                
                            }
                            exp_vars->res[exp_vars->k] = '\0';
                        }
                        else
                        {
                            if (itter->content[exp_vars->i] == '$' && ft_isdigit(itter->content[exp_vars->i + 1]))
                                exp_vars->i++;
                            else if (itter->content[exp_vars->i] == '$' && (itter->content[exp_vars->i + 1] == '\"' || itter->content[exp_vars->i + 1] == '\'') && itter->content[exp_vars->i + 2])
                                exp_vars->i++;
                            else
                                exp_vars->res = ft_strjoin(exp_vars->res, &itter->content[exp_vars->i]);
                        }
                        if (exp_vars->res[exp_vars->k])
                            exp_vars->k++;
                        if (itter->content[exp_vars->i])
                            exp_vars->i++;
                        exp_vars->res[exp_vars->k] = '\0';
                        // printf("%c\n", itter->content[i]);
                    }
                    if ((itter->content[exp_vars->i] == '\'' || itter->content[exp_vars->i]) && itter->content[exp_vars->i])
                        exp_vars->i++;
                }
            }
        }
        itter->content = ft_strdup(exp_vars->res);
        itter = itter->next;
    }
    
    return token;
}
