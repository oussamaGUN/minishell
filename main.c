#include "main.h"
char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src [j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char *ft_path(char **env)
{
    int i = 0;
    char **args;
    while (env[i])
    {
        args = ft_split(env[i], '=');
        if (strcmp(args[0], "PATH") == 0)
            return args[1];
        free(args[0]);
        free(args[1]);
        i++;
    }
    return NULL;
}
char *ft_getpath(char *cmd, char **env)
{
    if (cmd[0] == '/')
    {
        if (access(cmd, X_OK) == 0)
            return cmd;
        else
            return NULL;
    }
    char *str = ft_path(env);
    char **splited = ft_split(str, ':');
    char *path;
    int i = 0;
    while (splited[i])
    {
        path = ft_strjoin(ft_strcat(splited[i], "/"), cmd);
        if (access(path, X_OK) == 0)
            return path;
        i++;
    }
    return NULL;
}

void signals_handle(char *cmd)
{
    // handle signals and parsing here (i guess)
    if (ft_strncmp(cmd, "exit", 4) == 0)
        exit(0);
}
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
    if (ft_strchr(file_name, ' '))
        exit(1);
    int pid = fork();
    if (pid == 0)
    {
        mini->args = ft_split(args[0] , ' ');
        mini->path = ft_getpath(mini->args[0], env);
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
    if (ft_strchr(mini->cmd, '>') || ft_strnstr(mini->cmd, ">>", 2))
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
void ft_output_execution(mini_t *mini, char **env, char *cmd)
{
    int pid = fork();
    if (pid == -1)
        exit(1);
    if (pid == 0)
    {
        mini->args = ft_split(cmd , ' ');
        mini->path = ft_getpath(mini->args[0], env);
        dup2(mini->input, STDIN_FILENO);
        if (mini->flag_for_file == 1)
            dup2(mini->file_mulipipes ,STDOUT_FILENO);
        else
            dup2(STDOUT_FILENO, mini->fd[1]);
        close(mini->fd[1]);
        close(mini->fd[0]);
        if (execve(mini->path, mini->args, env) == -1)
        {
            printf("command not found\n");
            exit(1);
        }
    }
}
void ft_input_execution(mini_t *mini, char **env, char *cmd)
{
    int pid = fork();
    if (pid == -1)
        exit(1);
    if (pid == 0)
    {
        mini->args = ft_split(cmd , ' ');
        mini->path = ft_getpath(mini->args[0], env);
        dup2(mini->fd[1], STDOUT_FILENO);
        dup2(mini->input, STDIN_FILENO);
        close(mini->fd[0]);
        if (execve(mini->path, mini->args, env) == -1)
        {
            printf("command not found\n");
            exit(1);
        }
    }
}

void exec_first_cmd(mini_t *mini, char *cmd,char **env)
{
    int pid = fork();
    if (pid == -1)
        exit(1);
    if (pid == 0)
    {
        mini->args = ft_split(cmd , ' ');
        mini->path = ft_getpath(mini->args[0], env);
        dup2(mini->fd[1], STDOUT_FILENO);
        close(mini->fd[0]);
        if (execve(mini->path, mini->args, env) == -1)
        {
            printf("command not found\n");
            exit(1);
        }
    }
}
void ft_handle_redirection_multipipes(mini_t *mini, char **env)
{
    char **split = ft_split(mini->cmd, '>');
    char **piped_command = ft_split(split[0], '|');
    int j = 0;
    char *file_name = ft_strtrim(split[1], " ");
    if (ft_strchr(file_name, ' '))
        exit(1);
    mini->flag_for_file = 0;
    mini->file_mulipipes = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (mini->file_mulipipes == -1)
        exit(1);
    if (pipe(mini->fd) == -1)
        exit(1);
    exec_first_cmd(mini, piped_command[0], env);
    close(mini->fd[1]);
    int i = 1;
    while (piped_command[i])
    {
        wait(NULL);
        mini->input = mini->fd[0];
        if (pipe(mini->fd) == -1)
            exit(1);
        if (piped_command[i + 1] == NULL)
        {
            mini->flag_for_file = 1;
            ft_output_execution(mini, env, piped_command[i]);
        }
        else
            ft_input_execution(mini, env, piped_command[i]);
        close(mini->fd[1]);
        i++;
    }

}
void multiple_cmds(mini_t *mini, char **env)
{
    if (ft_strchr(mini->cmd, '>') || ft_strnstr(mini->cmd, ">>", 2))
    {
        ft_handle_redirection_multipipes(mini, env);
    }
    else
    {
        char **piped_command = ft_split(mini->cmd, '|');
        int j = 0;
    
        if (pipe(mini->fd) == -1)
            exit(1);
        exec_first_cmd(mini, piped_command[0], env);
        close(mini->fd[1]);
        int i = 1;
        while (piped_command[i])
        {
            wait(NULL);
            mini->input = mini->fd[0];
            if (pipe(mini->fd) == -1)
                exit(1);
            if (piped_command[i + 1] == NULL)
                ft_output_execution(mini, env, piped_command[i]);
            else
                ft_input_execution(mini, env, piped_command[i]);
            close(mini->fd[1]);
            i++;
        }
    }
}
char *ft_pipe_check(char *cmd)
{
    int i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '|')
            return cmd;
        i++;
    }
    return NULL;
}
void cmd_exe(mini_t *mini, char **env)
{
    mini->cmd = readline(ANSI_COLOR_GREEN  "→" ANSI_COLOR_RESET " ");
    add_history(mini->cmd);
    if (ft_pipe_check(mini->cmd))
    {
        multiple_cmds(mini, env);
    }
    else
        normal_cmd(mini, env);

    wait(NULL);

}
void execution(mini_t *mini, char **env)
{
    while (1)
    {
        cmd_exe(mini, env);
    }
    rl_clear_history();
}
int main(int ac , char *av[], char *env[])
{
    mini_t mini;
    
    execution(&mini, env);
}