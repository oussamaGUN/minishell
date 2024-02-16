#include "main.h"

void ft_lst_creat_env(mini_t *mini, char **env)
{
    t_list *list = NULL;
    t_list *new;
    int i = 0;
    while (env[i])
    {
        new = ft_lstnew(env[i]);
        ft_lstadd_back(&list, new);
        i++;
    }
    // t_list *lst = list;
    // while (lst)
    // {
    //     printf("%s\n", lst->content);
    //     lst = lst->next;
    // }
}