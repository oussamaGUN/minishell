#include "../main.h"

void cd(char **arr)
{
    if (!arr[1])
    {
        if (chdir("/Users/ousabbar") == -1)
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
        cd(lst->arr);
    }
    else if (ft_strncmp(lst->arr[0], "pwd", 3) == 0 || ft_strncmp(lst->arr[0], "PWD", 3) == 0)
    {
        printf("%s\n", lst->path);
    }
}