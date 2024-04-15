#include "main.h"

int	cmd_exe(t_token *token, t_env *env)
{
	t_token *new_token;
	t_token *cmd_list;
	char *cmd;
	int flag;

	cmd = readline("→ ");
	if (!cmd || ft_strncmp(cmd ,"exit", 4) == 0)
	{
		printf("exit\n");
		return 1;
	}
	add_history(cmd);
	token = NULL;
	flag = tokenizer(cmd, &token);
	if (!flag)
		return 0;
	if (!ft_check_errors(token))
		return 0;
	new_token = expanding(token, env);
	cmd_list = ft_list(new_token, env);
	if (!cmd_list)
		return 0;
	if (!execution(cmd_list, env))
		return 0;
	return 0;
}
int	main(int ac, char *av[], char *envp[])
{
	t_env			*env;

	env = envir(envp);
	while (!cmd_exe(NULL, env))
		;
	// rl_clear_history();
	return (EXIT_SUCCESS);
}