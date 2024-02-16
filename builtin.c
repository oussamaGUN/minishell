#include "main.h"

char *ft_getenv_cd(char *s, char **env)
{
	s += 1;
	return getenv(s);
}
void	ft_cd(mini_t *mini, char **env)
{
	if (mini->piped_command[2])
	{
		printf("cd: string not in pwd: %s\n", mini->piped_command[2]);
		return ;
	}
	if (!mini->piped_command[1])
		mini->piped_command[1] = ft_strdup("/home/oussama");
	if (ft_strchr(mini->piped_command[1], '$'))
		mini->piped_command[1] = ft_getenv_cd(mini->piped_command[1], env);
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

void ft_pwd(mini_t *mini, char **env)
{
    printf("%s\n", mini->current_path);
}