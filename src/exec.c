#include "main.h"
void	print_token(t_token *lst)
{
	printf("\t\t>>arr<<\n");
	for (int i = 0; lst->arr[i];i++)
		puts(lst->arr[i]);
	printf("fd[0] = %d -- fd[1] == %d\n",lst->fd[0],lst->fd[1]);
	printf("input_file %d\n",lst->input_file);
	printf("output_file %d\n",lst->output_file);
	printf("%s\n",lst->path);
	lst->next ? puts("next : √"):puts("next : x");
	lst->prev ? puts("prev : √"):puts("prev : x");
}





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
		close(lst->prev->fd[STDOUT_FILENO]);
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
		close(lst->fd[STDIN_FILENO]);
	}
}


int	exec_cmd(t_token *lst, t_env *env)
{

	set_io(lst);
	if (lst->path)
		if ((-1) == execve(lst->path, lst->arr, env->envp));
			printf("mini: %s: command not found\n",lst->path);
	exit(127);
}

int exec(t_token *lst, t_env *env)
{
	t_token	*cmdlist = lst;

	while (cmdlist)
	{
		if (cmdlist->next)
			pipe(cmdlist->fd);
		cmdlist->pid = fork();
		if (!cmdlist->pid)
			exit(exec_cmd(cmdlist, env));
		wait(&(cmdlist->exit_status));
		exit_status = cmdlist->exit_status;
		if (cmdlist->next)
			close(cmdlist->fd[STDOUT_FILENO]);
		cmdlist = cmdlist->next;
	}
}