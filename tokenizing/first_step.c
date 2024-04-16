#include "../main.h"

t_token	*new(void *content)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	if (!content)
		new->content = NULL;
	else
		new->content = (void *)content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
void	ft_lstadd(t_token **lst, t_token *new)
{
	t_token *tmp;

	if (lst == NULL || (*lst) == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}
void f_open(t_tokenizer *vars, t_token *node)
{
	if (vars->flag == 1)
		node->type = FILE_APP;
	else if (vars->flag == 2)
		node->type = FILE_OUT;
	else if (vars->flag == 3)
		node->type = FILE_IN;
	else if (vars->flag == 4)
		node->type = DELIMITER;
	else
		node->type = WORD;
	vars->flag = 0;
}
void token_type(char *sp, t_tokenizer *vars, t_token *node)
{
		if (ft_strncmp(sp, "|", 1) == 0)
			node->type = PIPE;
		else if (ft_strncmp(sp, ">>", 2) == 0)
		{
			vars->flag = 1;
			node->type = RED_APPEND;
		}
		else if (ft_strncmp(sp, ">", 1) == 0)
		{
			vars->flag = 2;
			node->type = RED_OUTPUT;
		}
		else if (ft_strncmp(sp, "<", ft_strlen(sp)) == 0)
		{
			vars->flag = 3;            
			node->type = RED_INPUT;
		}
		else if (ft_strncmp(sp, "<<", ft_strlen(sp)) == 0)
		{
			vars->flag = 4;
			node->type = HERE_DOC;
		}
}

int tokenizer(char *cmd, t_token **token, t_env **env)
{
	t_token     *node;
	t_tokenizer *vars;
	char        **sp;
	int         i;

	i = -1;
	vars = ft_malloc(sizeof(t_tokenizer), &((*env)->mem));
	puts("ft_malloc1");
	return (0);
	if (!vars)
		return (0);
	sp = ft_ownsplit(cmd, ' ', vars);
	free(cmd);// refactor ??
	if (!sp)
		return (free(vars), 0);
	vars->flag = 0;
	while (sp[++i])
	{
		node = new(sp[i]);
		if (ft_strncmp(sp[i], "|", 1) == 0 || ft_strncmp(sp[i], ">>", 2) == 0
			|| ft_strncmp(sp[i], ">", 1) == 0 || ft_strncmp(sp[i], "<", 1) == 0)
			token_type(sp[i], vars, node);
		else
			f_open(vars, node);
		ft_lstadd(token, node);
	}
	free2d(sp);
	return 1;
}
