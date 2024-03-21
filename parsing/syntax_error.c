#include "../main.h"

int syntax_error(t_token *token)
{
	t_token *s = token;
    // if ((s->type == PIPE || s->type == RED_OUTPUT || s->type == RED_APPEND || s->type == RED_INPUT) && s->next->type == WORD && )
    //     return 0;
	while (s)
	{
        if (s->type == PIPE)
        {

            if (!s->next)
                return 0;
            if (!s->prev)
                return 0;
            if (s->prev->type != WORD && s->prev->type != FILE_OUT && s->prev->type != FILE_IN && s->prev->type != FILE_APP)
                return 0;
            if (s->next->type != WORD)
                return 0;
        }
        else if (s->type == RED_OUTPUT)
        {
            if (!s->next)
                return 0;
            if (!s->prev)
                return 0;
            if (s->prev->type != WORD && s->prev->type != FILE_OUT && s->prev->type != FILE_IN && s->prev->type != FILE_APP)
                return 0;
            if (s->next->type != FILE_OUT)
                return 0;
        }
        else if (s->type == RED_INPUT)
        {
            if (!s->next)
                return 0;
            if (s->prev)
                if (s->prev->type != WORD && s->prev->type != FILE_OUT && s->prev->type != FILE_IN && s->prev->type != FILE_APP)
                    return 0;
            if (s->next->type != FILE_IN)
                return 0;
        }
        else if (s->type == RED_APPEND)
        {
            if (!s->next)
                return 0;
            if (!s->prev)
                return 0;
            if (s->prev->type != WORD && s->prev->type != FILE_OUT && s->prev->type != FILE_IN && s->prev->type != FILE_APP)
                return 0;
            if (s->next->type != FILE_APP)
                return 0;   
        }
        s = s->next;
	}
    return 1;
}