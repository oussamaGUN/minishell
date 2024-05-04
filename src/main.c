/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 06:57:52 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/04 12:26:52 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	g_exit_status;

void	ft_path(t_token *cmd_list, t_env *env)
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

t_env	*create_new_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->key = ft_strdup("PWD");
	env->value = getcwd(NULL, 0);
	env->next = malloc(sizeof(t_env));
	env->next->key = ft_strdup("PATH");
	env->next->value = ft_strdup(
			"/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	env->next->next = malloc(sizeof(t_env));
	env->next->next->key = ft_strdup("SHLVL");
	env->next->next->value = ft_strdup("0");
	env->next->next->next = NULL;
	return (env);
}

char	*create_promet(t_env *env)
{
	char	*promet;
	char	*buf;
	char	*tmp;

	buf = ft_malloc(0, &(env->mem), getcwd(NULL, 0));
	promet = ft_malloc(0, &(env->mem), ft_strjoin(CYAN, buf));
	if (g_exit_status)
		tmp = ft_malloc(0, &(env->mem), ft_strjoin(RED, "(✖)"));
	else
		tmp = ft_malloc(0, &(env->mem), ft_strjoin(GREEN, "(✔)"));
	buf = ft_malloc(0, &(env->mem), ft_strjoin(promet, tmp));
	tmp = ft_malloc(0, &(env->mem), ft_strjoin(buf, "$> "));
	promet = ft_malloc(0, &(env->mem), ft_strjoin(tmp, RESET));
	return (promet);
}

int	cmd_exe(t_token *token, t_env *env)
{
	t_token	*new_token;
	t_token	*cmd_list;
	char	*cmd;
	char	*promet;

	signals_for_parent();
	promet = create_promet(env);
	cmd = readline(promet);
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
	ft_path(cmd_list, env);
	return (exec(cmd_list, env));
}

int	main(int ac, char *av[], char *envp[])
{
	t_env	*env;

	if (ac || av)
		av = NULL;
	if (!(*envp))
		env = create_new_env();
	else
		env = envir(envp);
	env->envp = envp;
	if (!env)
		return (printf("exit\n"), EXIT_FAILURE);
	env->mem = NULL;
	while (!cmd_exe(NULL, env))
		garbage_collector(&env->mem);
	env_clear(&env);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
