#include "../main.h"


t_token *ft_check_errors(t_token *token)
{
    if (!syntax_error(token))
    {
        ft_putendl_fd("syntax error", 2);
        return NULL;
    }
    return token;
}