#include "main.h"

char *normal_path(char *cmd, t_env *env)
{
	int		j;
	char	**splited;
	char	*path;

	if (!ft_strlen(cmd))
		return (NULL);
	while (env)
	{
		splited = ft_split(env->value, ':');
		j = 0;
		while (splited[j])
		{
			path = ft_strjoin(ft_strjoin(splited[j], "/"), cmd);
			if (access(path, X_OK) == 0)
				return (path);
			free(path);
			j++;
		}
		env = env->next;
	}
	return (NULL);
}
char	*ft_getpath(char *cmd, t_env *env)
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
			return cmd;
	}
	return (cmd);
}
