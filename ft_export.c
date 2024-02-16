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

void ft_putsort(mini_t *mini, char **env)
{
    int j = 0;
    while (env[j])
        j++;
    char **str = malloc(sizeof(char *) * (j + 1));
    if (!str)
        return ;
    int i = 0;
    while (env[i])
    {
        str[i] = ft_strdup(env[i]);
        i++;
    }
    str[i] = NULL;
    char *tmp;
    i = 0;
    while (j >= 0)
    {
        while (str[i] && str[i + 1])
        {
            if (str[i][0] > str[i + 1][0])
            {
                tmp = ft_strdup(str[i]);
                str[i] = ft_strdup(str[i + 1]);
                str[i + 1] = ft_strdup(tmp);
            }
            i++;
        }
        i = 0;
        j--;
    }

    i = 0;
    while (str[i])
        printf("declare -x %s\n",str[i++]);
}

void    ft_export(mini_t *mini,char **env)
{
    char **sp = ft_split(mini->cmd, ' ');
    int i = 0;
    while (sp[i])
        i++;
    if (ft_strncmp(sp[0], "export", 6) == 0 && !sp[1])
        ft_putsort(mini, env);  
}