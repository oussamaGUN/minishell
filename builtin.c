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
char *ft_get_value(char *key, char **env)
{
	int i = 0;
	char **split;
	while (*key == '$')
		key++;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (strcmp(split[0], key) == 0)
			return split[1];
		i++;
	}
	return NULL;
}

void ft_echo(mini_t *mini, char **env, int exit_status)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		mini->args = ft_split(mini->cmd, ' ');
		mini->path = ft_getpath(mini->args[0], env);
		char *env_var;
		char **s;
		int i = 0;
		while (mini->args[++i])
		{
				
			if (ft_strnstr(mini->args[i], "$", ft_strlen(mini->args[i])))
			{
				s = ft_split(mini->args[i], '$');
				if (s[1])
					mini->args[i] = ft_strdup(s[1]);

				env_var = ft_get_value(mini->args[i], env);
				if (!env_var)
					mini->args[i] = ft_strjoin(s[0], "\n");
				else
				{
					if (s[1])
						mini->args[i] = ft_strjoin(s[0], env_var);
					else
						mini->args[i] = ft_strdup(env_var);
					// printf("%s\n", mini->args[i]);
				}
			}
		}
		if (execve(mini->path, mini->args, env) == -1)
		{
			printf("command not found\n");
			exit_status = EXIT_FAILURE;
			exit(EXIT_FAILURE);
		}
	}
}
void ft_pwd(mini_t *mini, char **env)
{
	char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        printf("%s\n", mini->current_path);
}