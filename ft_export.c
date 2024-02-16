#include "main.h"

t_list* ft_lst_creat_env(mini_t *mini, char **env)
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
    return list;
}

void ft_export(mini_t *mini, char **env)
{
    if (ft_strncmp(mini->cmd, "export", 6) == 0)
    {
        // int i = 0;
        // while (env[i])
        //     ft_putendl_fd(env[i++], 1);
    }
}