/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:02:34 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 23:15:46 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_cwd(t_env *env, char **cwd, bool print_err)
{
	if (print_err)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd:", 2);
		ft_putstr_fd(" cannot access parent directories:", 2);
		ft_putendl_fd(" No such file or directory", 2);
	}
	*cwd =  ft_strjoin(env->pwd, "/..");
}

int	cd(char **arr, t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		no_cwd(env, &cwd, true);
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
	set(env, ft_strdup("OLDPWD"), env->pwd, true);
	env = ft_update_pwd_env(env);
	return (0);
}
