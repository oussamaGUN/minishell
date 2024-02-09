#include "main.h"

void	check_builtin(mini_t *mini, char **env)
{
    mini->piped_command = ft_split(mini->cmd, ' ');
	if (!mini->piped_command)
		return ;
	if (cmp(mini->piped_command[0], "cd", 2) == 0)
    {
		if (chdir(mini->piped_command[1]) == -1)
        {
            int i = 0;
            while (mini->piped_command[i])
                free(mini->piped_command[i++]);
            free(mini->piped_command);
            printf("is not a dir\n");
            return ;
        }
    }
}