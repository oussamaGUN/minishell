/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:56:59 by melfersi          #+#    #+#             */
/*   Updated: 2024/04/30 11:50:31 by melfersi         ###   ########.fr       */
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

int	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("mini"), 1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	cd(char **arr, t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!arr[1])
	{
		if (chdir(get_value(env, "HOME")) == (-1))
			return (perror("mini"), 1);
		set(env, ft_strdup("OLDPWD"), cwd);
		return (0);
	}
	if (!ft_strcmp(arr[1], "-"))
		if (chdir(get_value(env, "OLDPWD")) == (-1))
			return (perror("mini"), 1);
	if (!ft_strcmp(arr[1], "~"))
		if (chdir(get_value(env, "HOME")) == (-1))
			return (perror("mini"), 1);
	if (ft_strncmp(arr[1], "~", 1) && ft_strncmp(arr[1], "-", 1))
		if (chdir(arr[1]) == (-1))
			return (perror("mini"), 1);
	set(env, ft_strdup("OLDPWD"), cwd);
	return (0);
}

t_env	*ft_update_pwd_env(t_env *env)
{
	char	*cwd;
	t_env	*p_env;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (env);
	p_env = env;
	while (p_env)
	{
		if (!ft_strcmp(p_env->key, "PWD"))
			p_env->value = cwd;
		p_env = p_env->next;
	}
	return (env);
}

int	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
