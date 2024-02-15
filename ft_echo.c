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
char *ft_new(char *s, char **env)
{
	char half[1024];
	int i = 0;
	while (*s != '$')
	{
		half[i] = *s;
		i++;
		s++;
	}
	half[i] = '\0';
	char **res = ft_split(s, '$');
	i = 0;
	while (res[i])
	{
		if (ft_get_value(res[i], env))
			res[i] = ft_strdup(ft_get_value(res[i], env));
		else
			res[i] = ft_strdup("");
		i++;
	}
	i = 0;
	char *ret = ft_strdup(half);
	while (res[i])
	{
		ret = ft_strjoin(ret, res[i]);
		i++;
	}
	return ret;
}
char **ft_split_env(char *str, char **env)
{
	char **s = ft_split(str, ' ');
	int i = 0;
	while (s[i])
	{
		if (ft_strchr(s[i], '$') && ft_strncmp(s[i], "$", ft_strlen(s[i])) == 1)
			s[i] = ft_new(s[i], env);
		i++;
	}
	return s;
}
void ft_echo(mini_t *mini, char **env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		mini->args = ft_split_env(mini->cmd, env);
		mini->path = ft_getpath(mini->args[0], env);

		if (execve(mini->path, mini->args, env) == -1)
		{
			printf("command not found\n");
			exit(EXIT_FAILURE);
		}
	}
}