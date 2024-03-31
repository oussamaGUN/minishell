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
int process_output(t_token *lst, t_env *env, int input)
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
        else
		    dup2(input, STDIN_FILENO);
		close(lst->fd[0]);
        close(lst->fd[1]);
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
int process_input(t_token *lst, t_env *env, int input)
{
    int id = fork();
    if (id == -1)
        return 0;
    else if (id == 0)
    {
        if (lst->output_file != -1)
            dup2(lst->output_file, STDOUT_FILENO);
        else
		    dup2(lst->fd[0], STDOUT_FILENO);
        if (lst->input_file != -1)
            dup2(lst->input_file, STDIN_FILENO);
        else
		    dup2(input, STDIN_FILENO);
		close(lst->fd[1]);
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
int exec_first_cmd(t_token *lst, t_env *env)
{
    int id = fork();
    if (id == -1)
        return 0;
    else if (id == 0)
    {
        if (lst->output_file != -1)
            dup2(lst->output_file, STDOUT_FILENO);
        else
            dup2(lst->fd[0], STDOUT_FILENO);
        if (lst->input_file != -1)
            dup2(lst->input_file, STDIN_FILENO);
        close(lst->fd[1]);
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
int multiple_cmd(t_token *lst, t_env *env)
{
    if (pipe(lst->fd) == -1)
        return 0;
    exec_first_cmd(lst, env);
    close(lst->fd[0]);
    lst = lst->next;
    int input;
    while (lst)
    {
        input = lst->fd[1];
        wait(NULL);
        if (pipe(lst->fd) == -1)
            return 0;
        if (!lst->next)
            process_output(lst, env, input);
        else
            process_input(lst, env, input);
        close(lst->fd[0]);
        lst = lst->next;
    }
    
    return 1;
}
int normal(t_token *lst, t_env *env)
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

int execution(t_token *lst, t_env *env)
{
    if (lstsize(lst) == 1)
    {
        if (normal(lst, env) == 0)
            return 0;
    }
    else
    {
        if (multiple_cmd(lst, env) == 0)
            return 0;
    }
    return 1;
}