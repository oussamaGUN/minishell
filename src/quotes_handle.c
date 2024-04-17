#include "main.h"


t_token *ft_check_errors(t_token *token)
{
    int flag = syntax_error(token);
    if (flag == 0)
    {
        ft_putendl_fd("syntax error", 2);
        return NULL;
    }
    else if (flag == 2)
        return NULL;
    return token;
}