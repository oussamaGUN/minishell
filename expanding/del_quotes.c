#include "../main.h"


char *ft_get(char *s)
{
    char **arr = ft_split(s, '$');
    char *env;
    char *res = "";
    int i = 0;
    while (arr[i])
    {
        env = getenv(arr[i]);
        if (env)
            res = ft_strjoin(res, env);
        else
            res = ft_strjoin(res, arr[i]);
        i++;
    }
    return res;
}
char *get_envir(char *s, char **env)
{
    char **arr = ft_split(s, ' ');
    char *res = "";
    int i = 0;
    while (arr[i])
    {
        if (ft_strchr(arr[i], '$'))
            res = ft_strjoin(res, ft_get(arr[i]));
        else
            res = ft_strjoin(res, arr[i]);
        if (arr[i + 1])
            res = ft_strjoin(res, " ");
        i++;
    }
    return res;
}

t_token *expanding(t_token *token, char **env)
{
    t_token *new_token;
    char *res = malloc(1);
    char *exp;
    int i = 0;
    int j = 0;
    int len = 0;
    while (token)
    {
        while (token->content[i])
        {
            if (token->content[i] == '\"')
            {
                len = ft_strlen(token->content);
                exp = malloc(sizeof(char) * len);
                i++;
                while (token->content[i] != '\"' && token->content[i])
                {
                    exp[j++] = token->content[i];
                    i++;
                }
                exp[j] = '\0';
                exp = get_envir(exp, env);
                res = ft_strjoin(res, exp);
                i++;
            }
            else if (token->content[i] == '\'')
            {
                len = ft_strlen(token->content);
                exp = malloc(sizeof(char) * len);
                i++;
                while (token->content[i] != '\'' && token->content[i])
                {
                    exp[j++] = token->content[i];
                    i++;
                }
                exp[j] = '\0';
                res = ft_strjoin(res, exp);
                i++;
            }
            else
            {
                len = ft_strlen(token->content);
                exp = malloc(sizeof(char) * len);
                while (token->content[i] != '\'' && token->content[i] != '\"' && token->content[i])
                {
                    exp[j++] = token->content[i];
                    i++;
                }
                exp[j] = '\0';
                exp = get_envir(exp, env);
                res = ft_strjoin(res, exp);
            }
            i++;
            printf("%s\n", res);
        }
    token = token->next;
    }
    return token;
}
