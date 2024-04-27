#include "main.h"

int	exit_status;

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

char	*prompt(void)
{
	char	*cmd;

	cmd = readline("$ ");
	if (!cmd)
		return (NULL);
	add_history(cmd);
	return (cmd);
}
int	cmd_exe(t_token *token, t_env *env)
{
	t_token	*new_token;
	t_token	*cmd_list;
	char	*cmd;

	signals_for_parent();
	cmd = prompt();
	if (!cmd)
		return (printf("exit\n"), 1);
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
