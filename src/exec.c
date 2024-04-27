#include "main.h"


void	set_io(t_token *lst)
{
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
}

int	exec_cmd(t_token *lst, t_env *env)
{
	if (lst->exit_status)
		exit (1);
	if (!lst->arr[0])
		exit(0);
	set_io(lst);
	builtins(lst, env);
	if (lst->path)
		execve(lst->path, lst->arr, env->envp);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("mini: %s: command not found\n",lst->path);
	exit(127);
}

void	exit_status_value(pid_t pid, int32_t *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		exit_status = WEXITSTATUS(*status);
	if (WIFSIGNALED(*status))
	{
		*status = WTERMSIG(*status);
		if (*status == 2)
			exit_status = 130;
		if (*status == 3)
			exit_status = 131;
	}
}


int exec(t_token *lst, t_env *env)
{
	signals_for_child();
	t_token	*cmdlist = lst;
	env = ft_update_pwd_env(env);
	if (!(cmdlist->next))
		exit_status = single_builtins(lst, env);
	if ((!(exit_status) && !(cmdlist->next))
		|| !ft_strcmp(cmdlist->arr[0], "exit"))
		return (0);
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
		exit_status_value(cmdlist->pid, &(cmdlist->exit_status));
		if (cmdlist->next)
			close(cmdlist->fd[STDOUT_FILENO]);
		cmdlist = cmdlist->next;
	}
	return (0);
}
