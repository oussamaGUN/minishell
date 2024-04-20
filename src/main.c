/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:36:30 by ousabbar          #+#    #+#             */
/*   Updated: 2024/04/19 18:44:33 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_path(t_token *cmd_list, char **env)
{
	t_token	*itter;
	
	itter = cmd_list;
	while (itter)
	{
		if (itter->arr[0])
			itter->path = ft_getpath(itter->arr[0], env);
		itter = itter->next;
	}
	return ;
	}
	
int	cmd_exe(t_token *token, t_env *env)
{
	t_token	*new_token;
	t_token	*cmd_list;
	char	*cmd;

	cmd = readline("$ ");
	if (!cmd)
		return (printf("exit\n"), 1);
	add_history(cmd);
	if (!tokenizer(cmd, &token, &env))
		return (0);
	if (!ft_check_errors(token))
		return (0);
	new_token = expanding(token, env);
	if (!new_token)
		return (0);
	cmd_list = ft_list(new_token, env);
	if (!cmd_list)
		return (0);
	ft_path(cmd_list, env->envp);
	if (!execution(cmd_list, env))
		return (0);
	return (0);
}

int	main(int ac, char *av[], char *envp[])
{
	t_env	*env;

	if (ac)
		av = NULL;
	env = envir(envp);
	env->envp = envp; 
	if (!env)
		return (printf("exit\n"), EXIT_FAILURE);
	env->mem = NULL;
	while (!cmd_exe(NULL, env))
		garbage_collector(&(env->mem));
	env_clear(&env);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
