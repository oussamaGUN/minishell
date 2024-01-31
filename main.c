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
void normal_cmd(mini_t *mini, char **env)
{
    signals_handle(mini->cmd);
    int pid = fork();
    if (pid == 0)
    {
        mini->args = ft_split(mini->cmd , ' ');
        mini->path = ft_getpath(mini->args[0], env);
        if (execve(mini->path, mini->args, env) == -1)
        {
            printf("command not found\n");
        }
    }
}
void multiple_cmds(char *cmd)
{
    printf("multiple cmds\n");
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
    int i = 0;
    while (mini->cmd[i] != ' ' && mini->cmd[i])
        i++;
    add_history(mini->cmd);
    if (ft_pipe_check(mini->cmd))
        multiple_cmds(mini->cmd);
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