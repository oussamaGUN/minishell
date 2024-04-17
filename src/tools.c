#include "main.h"

void del(void *s)
{
    free(s);
}
void	delone(t_token *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}
void	clear(t_token **lst, void (*del)(void *))
{
	t_token	*s;

	s = *lst;
    while (s && s->next)
    {
        printf("%s %d\n", s->content, s->type);
        s = s->next;
    }
	// if (s && del)
	// {
	// 	while (s)
	// 	{
	// 		s = s->next;
	// 		delone(*lst, del);
	// 		*lst = s;
	// 	}
	// 	*lst = NULL;
	// }
}
