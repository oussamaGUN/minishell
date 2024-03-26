#include "../main.h"


char *expand(char *s)
{
    char *env;
    env = getenv(s);
    if (env)
        return ft_strdup(env);
    return NULL;
}
t_token *expanding(t_token *token, char **env)
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
    res = malloc(ft_strlen(token->content) * 1);
    while (itter)
    {
        i = 0;
        k = 0;
        res[0] = '\0';
        while (itter->content[i])
        {
            if (itter->content[i] == '\"')
            {
                i++;
                while (itter->content[i] != '\"' && itter->content[i])
                {
                    j = 0;
                    if (itter->content[i] == '$' && itter->content[i + 1] != ' ' && itter->content[i + 1] != '\'' 
                        && itter->content[i + 1] != '\"' && itter->content[i + 1]&& !ft_isdigit(itter->content[i + 1]))
                    {
                        i++;
                        while (itter->content[i] != '$' && itter->content[i] != ' ' && itter->content[i] != '\'' 
                            && itter->content[i] != '\"' && ft_isalnum(itter->content[i]))
                        {
                            inside_dquotes[j] = itter->content[i];
                            i++;
                            j++;
                        }
                        inside_dquotes[j] = '\0';
                        exp = expand(inside_dquotes);
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
                            if (itter->content[i] == '\\')
                                i++;
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
                while (itter->content[i] != '\"' && itter->content[i] && itter->content[i] != '\'')
                {
                    j = 0;
                    if (itter->content[i] == '$' && itter->content[i + 1] != ' ' && itter->content[i + 1] != '\'' && itter->content[i + 1] != '\\'
                        && itter->content[i + 1] != '\"' && itter->content[i + 1] && !ft_isdigit(itter->content[i + 1]))
                    {
                        i++;
                        while (itter->content[i] != ' ' && itter->content[i] != '\'' && itter->content[i] != '\\' 
                            && itter->content[i] != '\"' && itter->content[i] && ft_isalnum(itter->content[i]))
                        {
                            inside_dquotes[j] = itter->content[i];
                            i++;
                            j++;
                        }
                        inside_dquotes[j] = '\0';
                        exp = expand(inside_dquotes);
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
                            if (itter->content[i] == '\\')
                                i++;
                            res = ft_strjoin(res, &itter->content[i]);
                        }
                    }
                    if (res[k])
                        k++;
                    if (itter->content[i])
                        i++;
                    res[k] = '\0';
                    // printf("%c\n", itter->content[i]);
                }
            }
        }
        itter->content = ft_strdup(res);
        itter = itter->next;
    }
    
    return token;
}
