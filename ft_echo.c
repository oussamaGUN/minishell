#include "main.h"

char *ft_get_value(char *key, char **env)
{
	int i = 0;
	char **split;   
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (strcmp(split[0], key) == 0)
			return split[1];
		i++;
	}
	return NULL;
}
char *joining(char **s)
{
    int i = 0;
    char *res = "";
    while (s[i])
    {
        res = ft_strjoin(res, s[i]);
        res = ft_strjoin(res, " ");
        i++;
    }
    return res;
}
char **ft_split_env(char *str)
{
    char **sp = ft_split(str, '$');
    char *string = joining(sp);
    char **res = ft_split(string, ' ');
    return res;
}
void ft_echo(mini_t *mini, char **env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		mini->args = ft_split_env(mini->cmd);
		mini->path = ft_getpath(mini->args[0], env);

		char *env_var;
		char **s;
		int i = 0;

		while (mini->args[++i])
		{
			    env_var = ft_get_value(mini->args[i], env);
				if (env_var)
					mini->args[i] = ft_strdup(env_var);
		}
		if (execve(mini->path, mini->args, env) == -1)
		{
			printf("command not found\n");
			exit(EXIT_FAILURE);
		}
	}
}