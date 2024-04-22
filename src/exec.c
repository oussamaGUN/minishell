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
	{
		if ((-1) == execve(lst->path, lst->arr, env->envp))
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
			printf("mini: %s: command not found\n",lst->path);
		}
	}
	exit(127);
}

int exec(t_token *lst, t_env *env)
{
	t_token	*cmdlist = lst;
	signal(SIGINT, SIG_DFL);
	signals_for_child();
	env = ft_update_pwd_env(env);
	if (!(cmdlist->next))
		if (!single_builtins(lst, env))
			return (0);
	while (cmdlist)
	{
		if (cmdlist->next)
			if ((-1) == pipe(cmdlist->fd))
				return (perror("pipe"), 1); // NEED TO PROTECT
		cmdlist->pid = fork();
		if ((-1) == cmdlist->pid)
			return (perror("fork"), 1);
		if (!cmdlist->pid)
			exec_cmd(cmdlist, env);
		wait(&(cmdlist->exit_status));
		exit_status = cmdlist->exit_status;
		if (cmdlist->next)
			close(cmdlist->fd[STDOUT_FILENO]);
		cmdlist = cmdlist->next;
	}
	return (0);
}
