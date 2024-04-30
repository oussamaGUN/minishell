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

char *get_path_dir(char *cmd)
{
	struct stat info;

	if (access(cmd, F_OK) == -1)
	{
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
		return (exit_status = 127, NULL);
	}
	stat(cmd, &info);
	if (S_ISDIR(info.st_mode))
	{
		ft_putendl_fd("Is a directory", STDERR_FILENO);
		return (exit_status = 126, NULL);
	}
	if (access(cmd, R_OK | X_OK) == -1)
	{
		ft_putendl_fd("Permission denied", STDERR_FILENO);
		return (exit_status = 126, cmd);
	}
	return (cmd);
}
char	*ft_getpath(char *cmd, t_env *env)
{
	char *str;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (!get_path_dir(cmd))
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

