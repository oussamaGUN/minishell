/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 07:00:04 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/07 19:39:14 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*normal_path(char *cmd, t_env *env)
{
	int		j;
	char	**splited;
	char	*path;
	t_free	**mem;

	mem = &(env->mem);
	if (!ft_strlen(cmd))
		return (NULL);
	while (env)
	{
		splited = ft_split(env->value, ':');
		j = 0;
		while (splited && splited[j])
		{
			path = ft_strjoin(ft_malloc(0,
						mem, ft_strjoin(splited[j++], "/")), cmd);
			if (access(path, X_OK) == 0)
				return (ft_free_env(splited), ft_malloc(0, mem, path));
			free(path);
		}
		ft_free_env(splited);
		env = env->next;
	}
	return (NULL);
}

char	*get_path_dir(char *cmd)
{
	struct stat	info;

	if (access(cmd, F_OK) == -1)
	{
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
		return (g_exit_status = 127, NULL);
	}
	stat(cmd, &info);
	if (S_ISDIR(info.st_mode))
	{
		ft_putendl_fd("Is a directory", STDERR_FILENO);
		return (g_exit_status = 126, NULL);
	}
	if (access(cmd, R_OK | X_OK) == -1)
	{
		ft_putendl_fd("Permission denied", STDERR_FILENO);
		return (g_exit_status = 126, cmd);
	}
	return (cmd);
}

char	*ft_getpath(char *cmd, t_env *env)
{
	char	*str;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (!get_path_dir(cmd))
			return (NULL);
	}
	else
	{
		str = normal_path(cmd, env);
		if (str)
			return (str);
		else
			return (cmd);
	}
	return (cmd);
}

char	*ft_getpathfor_underscore(char *cmd, t_env *env)
{
	char	*str;

	str = normal_path(cmd, env);
	if (str)
		return (str);
	else
		return (cmd);
	return (cmd);
}
