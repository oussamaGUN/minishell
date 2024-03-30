#include "../main.h"

char **env_arr(t_env *env)
{
    t_env *it = env;
    int len = 0;
    while (it)
    {
        len++;
        it = it->next;
    }
    char **arr;
    arr = malloc(sizeof(char *) * (len + 1));
    if (!arr)
        return NULL;
    int i = 0;
    t_env *itter = env;
    char *s = "\0";
    while (itter)
    {
        s = ft_strjoin(s, itter->key);
        s = ft_strjoin(s, "=");
        s = ft_strjoin(s, itter->value);
        arr[i] = ft_strdup(s);
        free(s);
        i++;
        itter = itter->next;
    }
    arr[i] = NULL;
    return arr;
}
int execution(t_token *lst, t_env *env)
{

    int id = fork();
    if (id == -1)
        return 0;
    else if (id == 0)
    {
        if (lst->output_file != -1)
            dup2(lst->output_file, STDOUT_FILENO);
        if (lst->input_file != -1)
            dup2(lst->input_file, STDIN_FILENO);
        char **envp = env_arr(env);
        char *path = ft_getpath(lst->arr[0], envp);
		if (execve(path, lst->arr, envp) == -1)
		{
			printf("bash: %s: command not found\n", lst->arr[0]);
			exit(EXIT_FAILURE);
		}
    }
    return 1;
}