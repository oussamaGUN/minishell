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
    char *normal;
    char *inside_dquotes;
    char *inside_squotes;
    char *cpy;
    char *exp;
    char *res;
    int i = 0;
    int k = 0;
    int j = 0;
    inside_dquotes = malloc(ft_strlen(token->content));
    t_token *itter = token;
    while (itter)
    {
        i = 0;
        k = 0;
        if (itter->type == DELIMITER)
        {
            res = malloc((ft_strlen(itter->content) + 1) * 1);
            while (itter->content[i])
            {
                if (itter->content[i] != '\'' && itter->content[i] != '\"')
                    res[j++] = itter->content[i];
                i++;
            }
            res[j] = '\0';
        }
        else
        {
            res = malloc((ft_strlen(itter->content) + 1) * 1);
            res[0] = '\0';
            while (itter->content[i])
            {
                if (itter->content[i] == '\"')
                {
                    i++;
                    while (itter->content[i] != '\"' && itter->content[i])
                    {
                        j = 0;
                        if (itter->content[i] == '$' && itter->content[i + 1] == '?')
                        {
                            i++;
                            while (itter->content[i] != '$' && itter->content[i] != ' ' 
                                && itter->content[i] != '\"' && ft_isalnum(itter->content[i]))
                                i++;
                            char *str = ft_itoa(exit_status >> 8);
                            res = ft_strjoin(res, str);
                            k = ft_strlen(res);
                            
                        }
                        else if (itter->content[i] == '$' && itter->content[i + 1] != ' ' && itter->content[i + 1] != '\'' 
                            && itter->content[i + 1] != '\"' && itter->content[i + 1]&& !ft_isdigit(itter->content[i + 1]))
                        {
                            i++;
                            while (itter->content[i] != '$' && itter->content[i] != ' ' 
                                && itter->content[i] != '\"' && ft_isalnum(itter->content[i]))
                            {
                                inside_dquotes[j] = itter->content[i];
                                i++;
                                j++;
                            }
                            inside_dquotes[j] = '\0';
                            exp = expand(inside_dquotes, env);
                            if (exp)
                            {
                                res = ft_strjoin(res, exp);
                                k = ft_strlen(res);
                            }
                            else
                                res = ft_strjoin(res, "");
                            i--;
                        }
                        else
                        {
                            if (itter->content[i] == '$' && ft_isdigit(itter->content[i + 1]))
                                i++;
                            else
                            {
    
                                res = ft_strjoin(res, &itter->content[i]);
                            }
                        }
                        if (res[k])
                            k++;
                        if (itter->content[i])
                            i++;
                        res[k] = '\0';
                    }
                    i++;

                }
                else if (itter->content[i] == '\'')
                {
                    i++;
                    while (itter->content[i] != '\'' && itter->content[i])
                    {
                        res = ft_strjoin(res, &itter->content[i]);
                        if (res[k])
                            k++;
                        if (itter->content[i])
                            i++;
                        
                    }
                    i++;
                    res[k] = '\0';
                }
                else
                {
                    while (itter->content[i] != '\"' && itter->content[i] != '\'' && itter->content[i])
                    {
                        j = 0;
                        if (itter->content[i] == '$' && itter->content[i + 1] == '?')
                        {
                            i++;
                            while (itter->content[i] != '$' && itter->content[i] != ' ' 
                                && itter->content[i] != '\"' && itter->content[i] != '\'' && ft_isalnum(itter->content[i]))
                                i++;
                            char *str = ft_itoa(exit_status >> 8);
                            res = ft_strjoin(res, str);
                            k = ft_strlen(res);
                        }
                        else if (itter->content[i] == '$' && itter->content[i + 1] != ' ' && itter->content[i + 1] != '\''
                            && itter->content[i + 1] != '\"' && itter->content[i + 1] && !ft_isdigit(itter->content[i + 1]))
                        {
                            i++;
                            while (itter->content[i] != ' ' 
                                && itter->content[i] != '\"' && itter->content[i] && ft_isalnum(itter->content[i]))
                            {
                                inside_dquotes[j] = itter->content[i];
                                i++;
                                j++;
                            }
                            inside_dquotes[j] = '\0';
                            exp = expand(inside_dquotes, env);
                            if (exp)
                            {
                                res = ft_strjoin(res, exp);
                                k = ft_strlen(res);
                            }
                            else
                                res = ft_strjoin(res, "");
                            i--;
                        }
                        else if (itter->content[i] == '\'')
                        {
                            i++;
                            while (itter->content[i] != '\'' && itter->content[i])
                            {
                                res = ft_strjoin(res, &itter->content[i]);
                                if (res[k])
                                    k++;
                                if (itter->content[i])
                                    i++;
                                
                            }
                            res[k] = '\0';
                        }
                        else
                        {
                            if (itter->content[i] == '$' && ft_isdigit(itter->content[i + 1]))
                                i++;
                            else if (itter->content[i] == '$' && (itter->content[i + 1] == '\"' || itter->content[i + 1] == '\'') && itter->content[i + 2])
                                i++;
                            else
                                res = ft_strjoin(res, &itter->content[i]);
                        }
                        if (res[k])
                            k++;
                        if (itter->content[i])
                            i++;
                        res[k] = '\0';
                        // printf("%c\n", itter->content[i]);
                    }
                    if ((itter->content[i] == '\'' || itter->content[i]) && itter->content[i])
                        i++;
                }
            }
        }
        itter->content = ft_strdup(res);
        itter = itter->next;
    }
    
    return token;
}
