#include "main.h"
int	lstsize(t_token *lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		while (lst)
		{
			i++;
			lst = lst->next;
		}
	}
	return (i);
}
char *normal_path(char *cmd, char **env)
{
	int		i;
	int		j;
	char	**str;
	char	**splited;
	char	*path;
	i = 0;
    
	while (env[i])
	{
		str = ft_split(env[i], '=');
		splited = ft_split(str[1], ':');
		j = 0;
		while (splited[j])
		{
			path = ft_strjoin(ft_strjoin(splited[j], "/"), cmd);
			if (access(path, X_OK) == 0)
				return (path);
			free(path);
			j++;
		}
		i++;
	}
	return NULL;
}
char	*ft_getpath(char *cmd, char **env)
{
	char *str;
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	else
	{
		str = normal_path(cmd, env);
		if (str)
			return str;
		else
			return cmd;
	}
	return (NULL);
}
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
    char *s;
    while (itter)
    {
        s = malloc(1);
        s = "\0";
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
    lst->pid = fork();
    if (lst->pid == -1)
        return 0;
    else if (lst->pid == 0)
    {
        if (lst->output_file != -1)
            dup2(lst->output_file, STDOUT_FILENO);
        if (lst->input_file != -1)
            dup2(lst->input_file, STDIN_FILENO);
        else
		    dup2(input, STDIN_FILENO);
		close(lst->fd[0]);
        close(lst->fd[1]);
        if (lst->arr[0] && (strcmp(lst->arr[0], "pwd") == 0|| strcmp(lst->arr[0], "PWD") == 0))
        {
            if (!builtins(lst, env))
                exit(127);
            exit(0);
        }
        else
        {
            if (lst->arr[0])
            {
                char **envp = env_arr(env);
                char *path = ft_getpath(lst->arr[0], envp);
                if (execve(path, lst->arr, envp) == -1)
                {
                    printf("bash: %s: command not found\n", lst->arr[0]);
                    exit(127);
                }
            }
            else
            {
                char **envp = env_arr(env);
                char *path = ft_getpath(lst->prev->arr[0], envp);
                if (execve(path, lst->prev->arr, envp) == -1)
                {
                    printf("bash: %s: command not found\n", lst->prev->arr[0]);
                    exit(127);
                }

            }
        }

    }
    else
        waitpid(lst->pid, &exit_status, 0);

    return 1;
}
int process_input(t_token *lst, t_env *env, int input)
{
    lst->pid = fork();
    if (lst->pid == -1)
        return 0;
    else if (lst->pid == 0)
    {
        if (lst->output_file != -1)
            dup2(lst->output_file, STDOUT_FILENO);
        else
		    dup2(lst->fd[1], STDOUT_FILENO);
        if (lst->input_file != -1)
            dup2(lst->input_file, STDIN_FILENO);
        else
		    dup2(input, STDIN_FILENO);
		close(lst->fd[0]);
        if (lst->arr[0] && (strcmp(lst->arr[0], "pwd") == 0|| strcmp(lst->arr[0], "PWD") == 0))
        {
            if (!builtins(lst, env))
                exit(127);
            exit(0);
        }
        else if (lst->arr[0])
        {
            char **envp = env_arr(env);
            char *path;
            path = ft_getpath(lst->arr[0], envp);
            if (execve(path, lst->arr, envp) == -1)
            {
                close(lst->fd[1]);
                ft_putstr_fd("bash: ", 2);
                ft_putstr_fd(lst->arr[0], 2);
                ft_putendl_fd(": command not found", 2);
                exit(127);
            }
        }
        else
        {
            close(lst->fd[1]);
            exit(0);
        }
    }
    return 1;
}
int exec_first_cmd(t_token *lst, t_env *env)
{
    lst->pid = fork();
    if (lst->pid == -1)
        return 0;
    else if (lst->pid == 0)
    {
        if (lst->output_file != -1)
            dup2(lst->output_file, STDOUT_FILENO);
        else
            dup2(lst->fd[1], STDOUT_FILENO);
        if (lst->input_file != -1)
            dup2(lst->input_file, STDIN_FILENO);
        close(lst->fd[0]);
        if (lst->arr[0] && (strcmp(lst->arr[0], "pwd") == 0|| strcmp(lst->arr[0], "PWD") == 0))
        {
            if (!builtins(lst, env))
                exit(127);
            exit(0);
        }
        else if (lst->arr[0])
        {
            char **envp = env_arr(env);
            char *path;
            path = ft_getpath(lst->arr[0], envp);
            if (execve(path, lst->arr, envp) == -1)
            {
                close(lst->fd[1]);
                ft_putstr_fd("bash: ", 2);
                ft_putstr_fd(lst->arr[0], 2);
                ft_putendl_fd(": command not found", 2);
                exit(127);
            }
        }
        else
        {
            close(lst->fd[1]);
            exit(0);
        }
    }
    return 1;
}
int multiple_cmd(t_token *lst, t_env *env)
{
    int exit_status;
    t_token *head = lst;
    if (pipe(lst->fd) == -1)
        return 0;
    exec_first_cmd(lst, env);
    close(lst->fd[1]);
    int input = lst->fd[0];
    lst = lst->next;
    while (lst)
    {
        if (pipe(lst->fd) == -1)
            return 0;
        if (!lst->next)
            process_output(lst, env, input);
        else
            process_input(lst, env, input);
        close(input);
        input = lst->fd[0];
        close(lst->fd[1]);
        lst = lst->next;
    }
    while (head)
    {
        waitpid(head->pid, &exit_status, 0);
        head = head->next;
    }
    return 1;
}
int normal(t_token *lst, t_env *env)
{

    if (lst->arr[0] && (ft_strncmp(lst->arr[0], "cd", 3) == 0 
        || ft_strncmp(lst->arr[0], "pwd", 4) == 0
        || ft_strncmp(lst->arr[0], "env", 4) == 0
        || ft_strncmp(lst->arr[0], "echo", 5) == 0))
    {
        if (!builtins(lst, env))
            return 0;
    }
    else
    {
        lst->pid = fork();
        if (lst->pid == -1)
            return 0;
        else if (lst->pid == 0)
        {
            if (lst->output_file != -1)
                dup2(lst->output_file, STDOUT_FILENO);
            if (lst->input_file != -1)
                dup2(lst->input_file, STDIN_FILENO);
            if (lst->arr[0])
            {
                char **envp = env_arr(env);

                char *path;
                path = ft_getpath(lst->arr[0], envp);
                // #!/bin/bash
                if (execve(path, lst->arr, envp) == -1)
                {
                    printf("bash: %s: command not found\n", lst->arr[0]);
                    exit(127);
                }
            }
            else
                exit(0);
        }
        else
            waitpid(lst->pid, &exit_status, 0);
    }
    return 1;

}

int execution(t_token *lst, t_env *env)
{
    // exec(lst, env);
    while (lst)
    {
        for (int i = 0;lst->arr[i];i++)
        {
            printf("%s\n", lst->arr[i]);
        }
        printf("%s %d %d\n", lst->path, lst->input_file, lst->output_file);
        printf("-------\n");
        lst = lst->next;
    }
    exit(1);
    env = ft_update_pwd_env(env);
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