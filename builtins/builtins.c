#include "../main.h"

char *ft_env(t_env *env, char *s)
{
    t_env *lst = env;
    while (lst)
    {
        if (ft_strncmp(lst->key, s, ft_strlen(s)) == 0)
            return lst->value;
        lst = lst->next;
    }
    return NULL;
}
void pwd(t_token *lst, t_env *env)
{
    char buff[4096];
	char *path;

	path = getcwd(buff, 4096);
    if (path == NULL)
        lst->path = ft_strdup(ft_env(env, "PWD"));
    else
	    lst->path = ft_strdup(path);
    t_env *itter = env;
    while (itter)
    {
        if (ft_strncmp(itter->key, "PWD", 4) == 0)
            itter->value = ft_strdup(lst->path);
        itter = itter->next;
    }
    printf("%s\n", lst->path);
}
void cd(char **arr, t_env *env)
{
    if (!arr[1])
    {
        if (chdir(ft_env(env, "HOME")) == -1)
        {
            perror("bash");
            return ;
        }
    }
    else if (chdir(arr[1]) == -1)
    {
        perror("bash");
        return ;
    }
}
void builtins(t_token *lst, t_env *env)
{
    if (ft_strncmp(lst->arr[0], "cd", 3) == 0 || ft_strncmp(lst->arr[0], "CD", 3) == 0)
    {
        cd(lst->arr, env);
    }
    else if (ft_strncmp(lst->arr[0], "pwd", 3) == 0 || ft_strncmp(lst->arr[0], "PWD", 3) == 0)
    {
        pwd(lst, env);
    }
}