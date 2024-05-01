#include "main.h"

t_token	*init(t_token *node, t_multx *vars, t_token *token, t_free **mem)
{
	if (!node)
		return (NULL);
	vars->count = ft_words(token);
	vars->i = 0;
	node->arr = (char **)ft_malloc(sizeof(char *) * (vars->count + 1), mem, NULL);
	if (!node->arr)
		return (NULL);
	node->output_file = -1;
	node->input_file = -1;
	node->exit_status = 0;
	node->status = 0;
	node->execute = token->execute;
	return (node);
}
t_token	*norm2(t_token *token, t_env *env, t_token *node, t_multx *vars)
{
	if (token->type == CMD && token->execute)
		node->arr[vars->i++] = ft_malloc(0, &(env->mem),
				ft_strdup(token->content));
	else if (!ft_openning_files(token, node))
		return (NULL);
	else if (token->type == DELIMITER)
	{
		if (!here_doc_implement(token, node, env))
			return (NULL);
	}
	if (node->exit_status == 1)
		node->status = 1;
	return (token);
}

int	ft_words(t_token *token)
{
	int		count;
	t_token	*itter;

	itter = token;
	count = 0;
	while (itter && itter->type != PIPE)
	{
		if (itter->type == CMD)
			count++;
		itter = itter->next;
	}
	return (count);
}
