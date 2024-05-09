/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:47:18 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/09 22:47:40 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*get_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	pwd(t_env *env)
{
	char	*cwd;

	if (env->pwd)
		printf("%s\n", env->pwd);
	else if (get_value(env, "PWD"))
		printf("%s\n", get_value(env, "PWD"));
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (perror("mini"), 1);
		printf("%s\n", cwd);
		free(cwd);
	}
	return (0);
}

int	cd(char **arr, t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!arr[1])
	{
		if (chdir(get_value(env, "HOME")) == (-1))
			return (free(cwd), perror("mini"), 1);
		set(env, ft_strdup("OLDPWD"), cwd, true);
		return (0);
	}
	if (!ft_strcmp(arr[1], "-"))
		if (chdir(get_value(env, "OLDPWD")) == (-1))
			return (free(cwd), perror("mini"), 1);
	if (!ft_strcmp(arr[1], "~"))
		if (chdir(get_value(env, "HOME")) == (-1))
			return (free(cwd), perror("mini"), 1);
	if (chdir(arr[1]) == (-1) && arr[1][0] != '~' && arr[1][0] != '-')
		return (free(cwd), perror("mini"), 1);
	set(env, ft_strdup("OLDPWD"), cwd, true);
	env = ft_update_pwd_env(env);
	return (0);
}

t_env	*ft_update_pwd_env(t_env *env)
{
	char	*cwd;
	char	tmp[4096];
	t_env	*p_env;

	cwd = getcwd(tmp, 4096);
	cwd = strdup(tmp);
	if (!cwd)
		cwd = ft_strdup(env->pwd);
	if (env->pwd)
		free(env->pwd);
	env->pwd = ft_strdup(cwd);
	p_env = env;
	while (p_env)
	{
		if (!ft_strcmp(p_env->key, "PWD"))
		{
			if (p_env->value != cwd)
				free(p_env->value);
			return (p_env->value = cwd, env);
		}
		p_env = p_env->next;
	}
	set(env, ft_strdup("PWD"), cwd, true);
	return (env);
}

int	print_env(t_env *env)
{
	while (env)
	{
		if (env->visible)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
