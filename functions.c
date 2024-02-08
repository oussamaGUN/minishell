#include "main.h"

void ft_handle_redirection(mini_t *mini, char **env)
{
    int file;
    char **args;
    char *file_name;
    if (strstr(mini->cmd, ">>"))
    {
        args = ft_split(mini->cmd, '>');
        int i = 1;
        while (args[i])
        {
            file_name = ft_strtrim(args[i], " ");
            file = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
            if (file == -1)
            {
                printf("%s: file not found\n", file_name);
                return ;
            }
            i++;
        }
    }
    else if (ft_strchr(mini->cmd, '>') && !strstr(mini->cmd, ">>"))
    {
        args = ft_split(mini->cmd, '>');
        int i = 1;
        while (args[i])
        {
            file_name = ft_strtrim(args[i], " ");
            file = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
            if (file == -1)
            {
               printf("%s: file not found\n", file_name);
                return ;
            }
            i++;
        }
    }
    else if (ft_strchr(mini->cmd, '<'))
    {
        args = ft_split(mini->cmd, '<');
        int i = 1;
        while (args[i])
        {
            file_name = ft_strtrim(args[i], " ");
            file = open(file_name, O_RDONLY);
            if (file == -1)
            {
                printf("%s: file not found\n", file_name);
                return ;
            }
            i++;
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
void ft_handle_redirection_one(mini_t *mini, char **env)
{
    char **split = ft_split(mini->cmd, ' ');
    int file_input = open(split[2], O_RDONLY);
    if (file_input == -1)
        exit(1);
    int file_output;
    if (mini->apah == 0)
        file_output = open(split[4], O_CREAT | O_RDWR | O_TRUNC, 0655);
    else if (mini->apah == 1)
        file_output = open(split[4], O_CREAT | O_RDWR | O_APPEND, 0655);
    if (file_output == -1)
        exit(1);
    int pid = fork();
    if (pid == 0)
    {
        dup2(file_input, STDIN_FILENO);
        dup2(file_output, STDOUT_FILENO);
        mini->args = ft_split(split[0], ' ');
        mini->path = ft_getpath(mini->args[0], env);
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
    if (strstr(mini->cmd, ">>") && ft_strchr(mini->cmd, '<'))
    {
        mini->apah = 1;
        ft_handle_redirection_one(mini, env);
    }
    else if (ft_strchr(mini->cmd, '>') && ft_strchr(mini->cmd, '<'))
    {
        mini->apah = 0;
        ft_handle_redirection_one(mini, env);
    }
    else if (ft_strchr(mini->cmd, '>') || ft_strchr(mini->cmd, '<')  || strstr(mini->cmd, ">>"))
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