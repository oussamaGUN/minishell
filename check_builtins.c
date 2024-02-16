#include "main.h"

void	check_builtin(mini_t *mini, char **env)
{
	mini->piped_command = ft_split(mini->cmd, ' ');
	if (!mini->piped_command)
		return ;
	if (ft_strncmp(mini->piped_command[0], "cd", 2) == 0)
        ft_cd(mini, env);
	else if (ft_strncmp(mini->piped_command[0], "pwd", 3) == 0)
        ft_pwd(mini, env);
    else if (ft_strncmp(mini->piped_command[0], "exit", 4) == 0)
    {
        if (mini->piped_command[1])
            exit(EXIT_FAILURE);
        else
            exit(EXIT_SUCCESS);
    }
    else if (ft_strncmp(mini->cmd, "export", 6) == 0)
        ft_export(mini, env);
}