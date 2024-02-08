#include "main.h"

void ft_handle(mini_t *mini, char **env, char *piped_command)
{
    char **exec = ft_split(piped_command, '>');
    mini->flag_for_file_output = 1;
    ft_output_execution(mini, env, exec[0]);
}
void ft_redirect_file(mini_t *mini, char **env)
{
    char **piped_command = ft_split(mini->cmd, '|');
    int i = 0;
    mini->j = 0;
    while (piped_command[i])
    {
        if (ft_strchr(piped_command[i], '>'))
        {
            char **redirect = ft_split(piped_command[i], '>');
            char *file_name = ft_strtrim(redirect[1], " ");
            if (ft_strchr(file_name, ' '))
                exit(1);
            mini->file_mulipipes = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
            if (mini->file_mulipipes == -1)
                return ;
            mini->j++;
        }
        i++;
    }
    if (mini->j > 1)
    {
        printf("invalid redirections\n");
        return ;
    }
    if (pipe(mini->fd) == -1)
        exit(1);
    exec_first_cmd(mini, piped_command[0], env);
    close(mini->fd[1]);
    i = 1;
    while (piped_command[i])
    {
        wait(NULL);
        mini->input = mini->fd[0];
        if (pipe(mini->fd) == -1)
            exit(1);
        if (ft_strchr(piped_command[i], '>') && !piped_command[i + 1])
            ft_handle(mini, env, piped_command[i]);
        else if (piped_command[i + 1] == NULL)
            ft_output_execution(mini, env, piped_command[i]);
        else
            ft_input_execution(mini, env, piped_command[i]);
        close(mini->fd[1]);
        mini->flag_for_file_output = 0;
        i++;
    }
    close(mini->file_mulipipes);
}
void ft_redirect_file_append(mini_t *mini, char **env)
{    
    char **piped_command = ft_split(mini->cmd, '|');
    int i = 0;
    mini->j = 0;
    while (piped_command[i])
    {
        if (ft_strchr(piped_command[i], '>'))
        {
            char **redirect = ft_split(piped_command[i], '>');
            char *file_name = ft_strtrim(redirect[1], " ");
            if (ft_strchr(file_name, ' '))
                exit(1);
            mini->file_mulipipes = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
            if (mini->file_mulipipes == -1)
                exit(1);
            mini->j++;
        }
        i++;
    }
    if (mini->j > 1)
    {
        printf("invalid redirections\n");
        return ;
    }
    if (pipe(mini->fd) == -1)
        exit(1);
    exec_first_cmd(mini, piped_command[0], env);
    close(mini->fd[1]);
    i = 1;
    while (piped_command[i])
    {
        wait(NULL);
        mini->input = mini->fd[0];
        if (pipe(mini->fd) == -1)
            exit(1);
        if (ft_strchr(piped_command[i], '>') && !piped_command[i + 1])
            ft_handle(mini, env, piped_command[i]);
        else if (piped_command[i + 1] == NULL)
            ft_output_execution(mini, env, piped_command[i]);
        else
            ft_input_execution(mini, env, piped_command[i]);
        close(mini->fd[1]);
        mini->flag_for_file_output = 0;
        i++;
    }
}
void ft_inputfilefor_multipipes_output(mini_t *mini, char **env, char *cmd)
{
    int pid = fork();
    if (pid == -1)
        exit(1);
    if (pid == 0)
    {
        mini->args = ft_split(cmd , ' ');
        mini->path = ft_getpath(mini->args[0], env);
        dup2(mini->file_input, STDIN_FILENO);
        if (mini->flag_for_file_input == 1)
            dup2(STDOUT_FILENO, mini->fd[1]);
        else if (mini->flag_for_file_input == 2)
            dup2(mini->fd[1], STDOUT_FILENO);
        if (execve(mini->path, mini->args, env) == -1)
        {
            printf("command not found\n");
            exit(1);
        }
    }
}
void ft_open_files_for_redirection(mini_t *mini)
{
    char **piped_command = ft_split(mini->cmd, '|');
    int i = 0;
    mini->j = 0;
    while (piped_command[i])
    {
        if (ft_strchr(piped_command[i], '>'))
        {
            char **redirect = ft_split(piped_command[i], '>');
            char *file_name = ft_strtrim(redirect[1], " ");
            if (ft_strchr(file_name, ' '))
                exit(1);
            mini->file_mulipipes = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
            if (mini->file_mulipipes == -1)
                exit(1);
            mini->j++;
        }
        i++;
    }
    if (mini->j > 1)
    {
        printf("invalid redirections\n");
        return ;
    }
}
void ft_inputfilefor_multipipes(mini_t *mini, char **env)
{
    char **piped_command = ft_split(mini->cmd, '|');

    int i = 0;
    while (piped_command[i])
    {
        if (ft_strchr(piped_command[i], '<'))
        {
            char **redirect = ft_split(piped_command[i], '<');
            char *file_name = ft_strtrim(redirect[1], " ");
            if (ft_strchr(file_name, ' '))
                exit(1);
            mini->file_input = open(file_name,  O_RDONLY);
            if (mini->file_mulipipes == -1)
                exit(1);
        }
        i++;
    }
    ft_open_files_for_redirection(mini);
    i = 0;
    while (piped_command[i])
    {
        if (ft_strchr(piped_command[i], '<'))
            break;
        i++;
    }
    char **re;
    while (piped_command[i])
    {
        if (pipe(mini->fd) == -1)
            exit(1);
        if (ft_strchr(piped_command[i], '<') && !piped_command[i + 1])
        {
            re = ft_split(piped_command[i], '<');
            mini->flag_for_file_input = 1;
            ft_inputfilefor_multipipes_output(mini, env, re[0]);
        }
        else if (ft_strchr(piped_command[i], '<') && piped_command[i + 1])
        {
            re = ft_split(piped_command[i], '<');
            mini->flag_for_file_input = 2;
            ft_inputfilefor_multipipes_output(mini, env, re[0]);
        }
        else if (ft_strchr(piped_command[i], '>') && !piped_command[i + 1])
        {
            re = ft_split(piped_command[i], '>');
            mini->flag_for_file_output = 1;
            ft_output_execution(mini, env, re[0]);
        }
        else if (piped_command[i + 1] == NULL)
        {
            ft_output_execution(mini, env, piped_command[i]);
        }
        else
            ft_input_execution(mini, env, piped_command[i]);
        wait(NULL);
        mini->input = mini->fd[0];
        close(mini->fd[1]);
        mini->flag_for_file_output = 0;
        i++;
    }
}


