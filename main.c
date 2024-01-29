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
void execution(mini_t *mini, char **env)
{
    char **args;
    char *path;

    while (1)
    {
        write(1, "$ ", 2);
        mini->cmd = readline("");
        args = ft_split(mini->cmd , ' ');
        int pid = fork();
        if (pid == 0)
        {
            path = ft_strjoin("/bin/", args[0]);
            if (execve(path, args, env) == -1)
            {
                printf("command not found\n");
                free(path);
            }
        }
        wait(NULL);
    }
}
int main(int ac , char *av[], char *env[])
{
    mini_t mini;
    execution(&mini, env);
}