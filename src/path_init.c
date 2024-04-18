#include "main.c"

char *normal_path(char *cmd, char **env)
{
	int		i;
	int		j;
	char	**str;
	char	**splited;
	char	*path;
	i = 0;
    
	while (env[i])
	{
		str = ft_split(env[i], '=');
		splited = ft_split(str[1], ':');
		j = 0;
		while (splited[j])
		{
			path = ft_strjoin(ft_strjoin(splited[j], "/"), cmd);
			if (access(path, X_OK) == 0)
				return (path);
			free(path);
			j++;
		}
		i++;
	}
	return NULL;
}
char	*ft_getpath(char *cmd, char **env)
{
	char *str;
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			return (NULL);
	}
	else
	{
		str = normal_path(cmd, env);
		if (str)
			return str;
		else
			return NULL;
	}
	return (NULL);
}