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
    int j = 0;
    while (splited[j])
        free(splited[j++]);
    return NULL;
}
void cmd_exe(mini_t *mini, char **env)
{
    write(1, "$ ", 2);
    mini->cmd = readline("");
    int pid = fork();
    if (pid == 0)
    {
        mini->args = ft_split(mini->cmd , ' ');
        mini->path = ft_getpath(mini->args[0], env);
        if (execve(mini->path, mini->args, env) == -1)
        {
            printf("command not found\n");
            free(mini->path);
        }
    }
    wait(NULL);
}
void execution(mini_t *mini, char **env)
{
    while (1)
    {
        cmd_exe(mini, env);
    }
}
int main(int ac , char *av[], char *env[])
{
    mini_t mini;
    execution(&mini, env);
}