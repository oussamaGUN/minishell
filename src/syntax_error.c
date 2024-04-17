#include "main.h"

int pipe_error(t_token *s)
{
    if (!s->next)
        return 0;
    if (!s->prev)
        return 0;
    if (s->prev->type != CMD && s->prev->type != FILE_OUT 
    && s->prev->type != FILE_IN && s->prev->type != FILE_APP && s->prev->type != DELIMITER)
        return 0;
    if (s->next->type != CMD && s->next->type != RED_OUTPUT && s->next->type != RED_APPEND)
        return 0;
    return 1;
}
int red_output_error(t_token *s)
{
    if (!s->next)
        return 0;
    if (!s->prev)
        return 1;
    if (s->prev)
        if (s->prev->type != CMD && s->prev->type != FILE_OUT && s->prev->type != PIPE
        && s->prev->type != FILE_IN && s->prev->type != FILE_APP && s->prev->type != DELIMITER)
            return 0;
    if (s->next->type != FILE_OUT)
        return 0;
    return 1;
}
int red_input_error(t_token *s)
{
    if (!s->next)
        return 0;
    if (!s->prev)
        return 1;
    if (s->prev)
    {
        if (s->prev->type != CMD && s->prev->type != FILE_OUT 
        && s->prev->type != FILE_IN && s->prev->type != FILE_APP && s->prev->type != DELIMITER)
            return 0;
    }
    if (s->next->type != FILE_IN)
        return 0;
    return 1;
}
int red_append_error(t_token *s)
{
    if (!s->next)
        return 0;
    if (!s->prev)
        return 1;
    if (s->prev)
        if (s->prev->type != CMD && s->prev->type != FILE_OUT && s->prev->type != PIPE
        && s->prev->type != FILE_IN && s->prev->type != FILE_APP && s->prev->type != DELIMITER)
            return 0;
    if (s->next->type != FILE_APP)
        return 0;
    return 1;
}
int here_doc_error(t_token *s)
{
    if (!s->next)
        return 0;
    if (s->prev)
        if (s->prev->type != CMD && s->prev->type != FILE_OUT 
        && s->prev->type != FILE_IN && s->prev->type != FILE_APP && s->prev->type != DELIMITER)
            return 0;
    if (s->next->type != DELIMITER)
        return 0;
    return 1;
}
int redirections_error(t_token *s)
{
    int flag;
    if (s->type == RED_OUTPUT)
    {
        flag = red_output_error(s);
        if (!flag)
            return 0;
        else if (flag == 2)
            return 2;
    }
    else if (s->type == RED_INPUT)
    {
        if (!red_input_error(s))
            return 0;
    }
    else if (s->type == RED_APPEND)
    {
        flag = red_append_error(s);
        if (!flag)
            return 0;
        else if (flag == 2)
            return 2;
    }
    return 1;
}
int file_errors(t_token *s)
{
    if (s->type == FILE_IN)
    {
        if (!s->prev->prev && !s->next)
            return 2;
    }
    return 1;
}
int errors(t_token *s)
{
    int flag;
    if (s->type == PIPE)
    {
        if (!pipe_error(s))
            return 0;
    }
    if (s->type == RED_OUTPUT || s->type == RED_INPUT
        || s->type == RED_APPEND)
    {
        flag = redirections_error(s);
        if (!flag)
            return 0;
        else if (flag == 2)
            return 2;
    }
    else if (s->type == HERE_DOC)
    {
        if (!here_doc_error(s))
            return 0;
    }
    else if (s->type == FILE_IN || s->type == DELIMITER)
    {
        int flag = file_errors(s);
        if (flag == 2)
            return 2;
        else
            return 1;
    }
    return 1;
}
int syntax_error(t_token *token)
{
	t_token *s;
    int flag;
    s = token;
	while (s)
	{
        flag = errors(s);
        if (!flag)
            return 0;
        else if (flag == 2)
            return 2;
        s = s->next;
	}
    return 1;
}
