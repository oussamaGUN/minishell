/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:52:56 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/06 18:10:09 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_io(t_token *lst)
{
	if (lst->input_file == (-2) || lst->output_file == (-2))
		return (-2);
	if (lst->input_file != (-1))
		dup2(lst->input_file, STDIN_FILENO);
	else if (lst->prev)
		dup2(lst->prev->fd[STDIN_FILENO], STDIN_FILENO);
	if (lst->output_file != (-1))
		dup2(lst->output_file, STDOUT_FILENO);
	else if (lst->next)
	{
		dup2(lst->fd[STDOUT_FILENO], STDOUT_FILENO);
		close(lst->fd[STDIN_FILENO]);
	}
	return (0);
}

int	exec_cmd(t_token *lst, t_env *env)
{
	if (lst->input_file == (-2) || lst->output_file == (-2))
		exit(1);
	if (set_io(lst))
		exit(1);
	if (!lst->arr[0] || lst->exit_status)
		exit(0);
	builtins(lst, env);
	if (lst->path)
	{
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

void	close_fds(t_token *lst)
{
	while (lst)
	{
		if (lst->next)
		{
			close(lst->fd[STDIN_FILENO]);
			close(lst->fd[STDOUT_FILENO]);
		}
		lst = lst->next;
	}
}

int	exec(t_token *lst, t_env *env)
{
	t_token	*cmdlist;
	t_token	*tmp;

	signals_for_child();
	cmdlist = lst;
	tmp = lst;
	env = ft_update_pwd_env(env);
	if (!(cmdlist->next))
		cmdlist->exit_status = single_builtins(lst, env);
	if (cmdlist->exit_status != (-2) && !cmdlist->next)
		return (g_exit_status = cmdlist->exit_status, 0);
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
