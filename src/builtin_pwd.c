/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:01:07 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:16:17 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
