#include "../main.h"

int syntax_error(t_token *token)
{
	t_token *s = token;
    t_token *prev = s;
    if (s->type == PIPE && s->next->type != 0)
            return 0;
    if (s)
        s = s->next;
	while (s != NULL)
	{
        if (s->type == PIPE && (s->next->type != WORD || prev->type != WORD))
            return 0;
        s = s->next;
        prev = prev->next;
	}
    return 1;
}