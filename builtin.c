#include "main.h"

void	ft_cd(mini_t *mini, char **env)
{
	if (!mini->piped_command[1])
		mini->piped_command[1] = ft_strdup("/home/oussama");
	if (chdir(mini->piped_command[1]) == -1)
	{
		printf("cd: no such file or directory: %s\n", mini->piped_command[1]);
		int i = 0;
		while (mini->piped_command[i])
			free(mini->piped_command[i++]);
		free(mini->piped_command);
		return ;
	}
}
void ft_echo(mini_t *mini, char **env, int exit_status)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		mini->args = ft_split(mini->cmd, ' ');
		mini->path = ft_getpath(mini->args[0], env);
		if (execve(mini->path, mini->args, env) == -1)
		{
			printf("command not found\n");
            exit_status = EXIT_FAILURE;
			exit(EXIT_FAILURE);
		}
	}
}