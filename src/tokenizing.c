/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 07:05:19 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:16:17 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_token(void *content, t_free **alloc)
{
	t_token	*buff;

	buff = (t_token *)ft_malloc(sizeof(t_token), alloc, NULL);
	if (!buff)
		return (NULL);
	if (!content)
		buff->content = NULL;
	else
		buff->content = content;
	buff->next = NULL;
	buff->prev = NULL;
	return (buff);
}

void	ft_lstadd(t_token **lst, t_token *new)
{
	t_token	*tmp;

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

void	f_open(t_tokenizer *vars, t_token *node)
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
		node->type = CMD;
	vars->flag = 0;
}

void	token_type(char *sp, t_tokenizer *vars, t_token *node)
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

int	tokenizer(char *cmd, t_token **token, t_env **env)
{
	t_token		*node;
	t_tokenizer	*vars;
	char		**sp;
	int			i;

	i = -1;
	vars = (t_tokenizer *)ft_malloc(sizeof(t_tokenizer), &((*env)->mem), NULL);
	if (!vars)
		return (free(cmd), 0);
	sp = ft_ownsplit(cmd, ' ', vars, &((*env)->mem));
	free(cmd);
	if (!sp)
		return (0);
	vars->flag = 0;
	while (sp[++i])
	{
		node = add_token(sp[i], &((*env)->mem));
		if (ft_strncmp(sp[i], "|", 1) == 0 || ft_strncmp(sp[i], ">>", 2) == 0
			|| ft_strncmp(sp[i], ">", 1) == 0 || ft_strncmp(sp[i], "<", 1) == 0)
			token_type(sp[i], vars, node);
		else
			f_open(vars, node);
		ft_lstadd(token, node);
	}
	return (1);
}
