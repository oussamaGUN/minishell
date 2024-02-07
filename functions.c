#include "main.h"

void ft_handle_redirection(mini_t *mini, char **env)
{
    int file;
    char **args;
    char *file_name;
    if (strstr(mini->cmd, ">>"))
    {
        args = ft_split(mini->cmd, '>');
        file_name = ft_strtrim(args[1], " ");
        file = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
        if (file == -1)
            exit(1);
    }
    else if (ft_strchr(mini->cmd, '>') && !strstr(mini->cmd, ">>"))
    {
        args = ft_split(mini->cmd, '>');
        file_name = ft_strtrim(args[1], " ");
        file = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (file == -1)
            exit(1);
    }
    else if (ft_strchr(mini->cmd, '<'))
    {
        args = ft_split(mini->cmd, '<');
        file_name = ft_strtrim(args[1], " ");
        file = open(file_name, O_RDONLY);
        if (file == -1)
        {
            printf("no hehe\n");
            exit(1);
        }
        mini->flag_for_file_input = 1;
    }
    if (ft_strchr(file_name, ' '))
        exit(1);
    int pid = fork();
    if (pid == 0)
    {
        mini->args = ft_split(args[0] , ' ');
        mini->path = ft_getpath(mini->args[0], env);
        if (mini->flag_for_file_input == 1)
        {
            dup2(file, STDIN_FILENO);
        }
        else
            dup2(file, STDOUT_FILENO);
        if (execve(mini->path, mini->args, env) == -1)
        {
            printf("command not found\n");
            exit(1);
        }
    }
}
void normal_cmd(mini_t *mini, char **env)
{
    signals_handle(mini->cmd);
    if (ft_strchr(mini->cmd, '>') || ft_strchr(mini->cmd, '<')  || ft_strnstr(mini->cmd, ">>", 2))
        ft_handle_redirection(mini, env);
    else
    {
        int pid = fork();
        if (pid == 0)
        {
            mini->args = ft_split(mini->cmd , ' ');
            mini->path = ft_getpath(mini->args[0], env);
            if (execve(mini->path, mini->args, env) == -1)
            {
                printf("command not found\n");
                exit(1);
            }
        }
    }
}