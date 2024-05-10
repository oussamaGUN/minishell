/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:02:34 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:16:17 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
