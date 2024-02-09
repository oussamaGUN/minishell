#include "main.h"

void	check_builtin(mini_t *mini, char **env)
{
	mini->piped_command = ft_split(mini->cmd, ' ');
	if (!mini->piped_command)
		return ;
	if (cmp(mini->piped_command[0], "cd", 2) == 0)
        ft_cd(mini, env);
}