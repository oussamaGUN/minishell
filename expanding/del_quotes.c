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
    while (token)
    {
        inside_dquotes = malloc(ft_strlen(token->content) * 100);
        res = malloc(ft_strlen(token->content) * 100);
        res[0] = '\0';
        while (token->content[i])
        {
            if (token->content[i] == '\"')
            {
                i++;
                while (token->content[i] != '\"' && token->content[i])
                {
                    j = 0;
                    if (token->content[i] == '$' && token->content[i + 1] != ' ' && token->content[i + 1] != '\'' && token->content[i + 1] != '\"' && token->content[i + 1])
                    {
                        i++;
                        while (token->content[i] != '$' && token->content[i] != ' ' && token->content[i] != '\'' && token->content[i] != '\"')
                        {
                            inside_dquotes[j] = token->content[i];
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
                        res[k] = token->content[i];
                    if (res[k])
                        k++;
                    i++;
                }
                res[k] = '\0';

            }
            i++;
        }
                    printf("%s %c\n", res, token->content[i]);
        token = token->next;
    }
    
    return token;
}
