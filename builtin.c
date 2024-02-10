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
	mini->piped_command = ft_split(mini->cmd, ' ');
	if (!mini->piped_command[1])
	{
		printf("\n");
		return ;
	}
	int i = 0;
	int flag = 0;
	if (cmp(mini->piped_command[1], "-n", 2) == 0)
	{
		flag = 1;
		i++;
	}
	i += 1;
	while (mini->piped_command[i])
	{
		if (cmp(mini->piped_command[i], "$?", 2) == 0)
			ft_putnbr_fd(exit_status, 1);
		else
			ft_putstr_fd(mini->piped_command[i], 1);
		i++;
		if (mini->piped_command[i])
			write(1, " ", 1);
	}
	if (flag == 0)
		printf("\n");
}