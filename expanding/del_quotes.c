#include "../main.h"

t_token *expanding(t_token *token)
{
    t_token *new_token;
    char *res;
    int i = 0;
    int j = 0;
    int len = 0;
    int flag = 0;
    while (token)
    {
        len = ft_strlen(token->content);
        res = malloc(sizeof(char) * len);
        while (token->content[i])
        {
            if (token->content[i] == '\"')
            {
                flag = 1;
                i++;
                while (token->content[i] != '\"' && token->content[i])
                
                    res[j++] = token->content[i++];
                i++;
            }
            res[j++] = token->content[i];
            i++;
        }
    }
    return token;
}
