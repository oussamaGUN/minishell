#include "main.h"

int here_doc(t_token *token)
{
    t_token *new = token;
    char *s;
    while (new)
    {
        if (new->type == HERE_DOC)
            if (new->next)
                s = ft_strdup(new->next->content);
        new = new->next;
    }
    return 1;
}