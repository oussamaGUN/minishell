#include "../main.h"
t_token	*ft_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
void	ft_lstadd(t_token **lst, t_token *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
t_token *tokenizer(char *str)
{
    char **sp = ft_ownsplit(str, ' ');
    if (!sp)
        return NULL;
    for (int i = 0;sp[i];i++)
        printf("%s\n", sp[i]);
    t_token *lst;
    t_token *node;
    int i = 0;
    int flag = 0;
    while (sp[i])
    {
        node = malloc(sizeof(t_token));
        node->content = ft_strdup(sp[i]);
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
        else if (ft_strncmp(sp[i], "<", 1) == 0)
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
        ft_lstadd(&lst, node);
        i++;
    }
    int j = 0;
    while (sp[j])
        free(sp[j++]);
    free(sp);
    return lst;
}