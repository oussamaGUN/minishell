#include "../main.h"

t_token	*new(void *content)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	if (!content)
		new->content = NULL;
	else
		new->content = (void *)content;
	new->next = NULL;
    new->prev = NULL;
	return (new);
}
void	ft_lstadd(t_token **lst, t_token *new)
{
	t_token *tmp;

	if (lst == NULL || (*lst) == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}
int tokenizer(char *str, t_token **token)
{
    char **sp = ft_ownsplit(str, ' ');

    
    if (!sp)
        return 0;
    t_token *node;
    int i = 0;
    int flag = 0;
    while (sp[i])
    {
        node = new(sp[i]);
        if (ft_strncmp(sp[i], "|", 1) == 0)
            node->type = PIPE;
        else if (ft_strncmp(sp[i], ">>", 2) == 0)
        {
            if (sp[i + 1])
                flag = 1;
            node->type = RED_APPEND;
        }
        else if (ft_strncmp(sp[i], "<<", 2) == 0)
            node->type = HER_DOC;
        else if (ft_strncmp(sp[i], ">", 1) == 0)
        {
            if (sp[i + 1])
                flag = 2;
            node->type = RED_OUTPUT;
        }
        else if (ft_strncmp(sp[i], "<", 2) == 0)
        {
            if (sp[i + 1])
                flag = 3;            
            node->type = RED_INPUT;
        }
        else
        {
            if (flag == 1)
                node->type = FILE_APP;
            else if (flag == 2)
                node->type = FILE_OUT;
            else if (flag == 3)
                node->type = FILE_IN;
            else
                node->type = WORD;
            flag = 0;
        }
        ft_lstadd(token, node);
        i++;
    }
    return 1;
}
