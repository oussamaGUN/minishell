#include "../main.h"

void	ft_lstadd(t_token **lst, t_token *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}
t_token *tokenizer(char *str)
{
    char **sp = ft_split(str, ' ');
    t_token *lst;
    t_token *node;
    int i = 0;
    while (sp[i])
    {
        node = malloc(sizeof(t_token));
        node->content = ft_strdup(sp[i]);
        if (ft_strncmp(sp[i], "|", 1) == 0)
            node->type = PIPE;
        else if (ft_strncmp(sp[i], ">>", 2) == 0 && ft_strlen(sp[i]) == 2)
            node->type = APPEND;
        else if (ft_strncmp(sp[i], "<<", 2) == 0 && ft_strlen(sp[i]) == 2)
            node->type = HER_DOC;
        else if (ft_strncmp(sp[i], ">", 1) == 0)
            node->type = REDIRECT;
        else if (ft_strncmp(sp[i], "<", 1) == 0)
            node->type = INPUT;
        else
            node->type = COMMAND;
        ft_lstadd(&lst, node);
        i++;
    }
    return lst;
}