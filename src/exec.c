#include "main.h"



void	set_io(t_token *lst)
{
	if (lst->input_file != (-1))
	{
		close(STDIN_FILENO);
		dup2(lst->input_file, STDIN_FILENO);
	}
	else if (lst->prev)
	{
		close(STDIN_FILENO);
		dup2(lst->prev->fd[STDIN_FILENO], STDIN_FILENO);
	}
	if (lst->output_file != (-1))
	{
		close(STDOUT_FILENO);
		dup2(lst->output_file, STDOUT_FILENO);
	}
	else if (lst->next)
	{
		close(STDOUT_FILENO);
		dup2(lst->fd[STDOUT_FILENO], STDOUT_FILENO);
	}
}

void	exec_cmd(t_token *lst, t_env *env)
{
	set_io(lst);
	execve(lst->arr[0], lst->arr, env->envp);
}

int exec(t_token *lst, t_env *env)
{
	t_token	*cmdlist = lst;

	while (cmdlist)
	{
		cmdlist->pid = fork();
		if (!cmdlist->pid)
		{
			exec_cmd(lst, env);
		}
		wait(&(cmdlist->exit_status));
		cmdlist = cmdlist->next;
	}
}