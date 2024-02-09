#include "main.h"

void	normal_cmd(mini_t *mini, char **env)
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
			exit(1);
		}
	}
}
