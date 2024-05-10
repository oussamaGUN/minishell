/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:53:29 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 21:44:19 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_token *lst, t_env *env)
{
	echoctl(ON);
	if (lst->input_file == (-2) || lst->output_file == (-2))
		exit(1);
	if (set_io(lst))
		exit(1);
	if (!lst->arr[0] || lst->exit_status)
		exit(0);
	builtins(lst, env);
	if (lst->path)
	{
		echoctl(ON);
		execve(lst->path, lst->arr, env_to_arr(env));
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("mini: %s: command not found\n", lst->path);
		exit(127);
	}
	exit(126);
}

void	exit_status_value(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		g_exit_status = WEXITSTATUS(*status);
	if (WIFSIGNALED(*status))
	{
		*status = WTERMSIG(*status);
		if (*status == 2)
			g_exit_status = 130;
		if (*status == 3)
			g_exit_status = 131;
	}
}

int	cmd_loop(t_token *cmdlist, t_env *env)
{
	t_token	*tmp;

	tmp = cmdlist;
	while (cmdlist)
	{
		if (cmdlist->next)
			if ((-1) == pipe(cmdlist->fd))
				return (perror("pipe"), 1);
		cmdlist->pid = fork();
		if ((-1) == cmdlist->pid)
			return (perror("fork"), 1);
		if (!cmdlist->pid)
			exec_cmd(cmdlist, env);
		if (cmdlist->next)
			close(cmdlist->fd[STDOUT_FILENO]);
		cmdlist = cmdlist->next;
	}
	return (0);
}

int	exec(t_token *lst, t_env *env)
{
	t_token	*cmdlist;
	t_token	*tmp;

	signals_for_child();
	cmdlist = lst;
	tmp = lst;
	if (!(cmdlist->next))
		cmdlist->exit_status = single_builtins(lst, env);
	if (cmdlist->exit_status != (-2) && !cmdlist->next)
		return (reset_io(lst), g_exit_status = cmdlist->exit_status, 0);
	cmdlist->exit_status = 0;
	if (cmd_loop(cmdlist, env))
		return (1);
	close_fds(cmdlist);
	while (tmp)
	{
		exit_status_value(tmp->pid, &tmp->exit_status);
		tmp = tmp->next;
	}
	return (0);
}
