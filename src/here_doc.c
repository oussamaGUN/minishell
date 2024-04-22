/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:35:41 by ousabbar          #+#    #+#             */
/*   Updated: 2024/04/22 15:21:34 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "main.h"

char	*here_doc_expand(char *s, t_env *env)
{
	t_multx	*vars;

	vars = (t_multx *)ft_malloc(sizeof(t_multx), &(env->mem), NULL);
	vars->inside_dquotes = ft_malloc(ft_strlen(s), &(env->mem), NULL);
	vars->res = ft_malloc(1, &(env->mem), NULL);
	if (!vars || !vars->inside_dquotes || !vars->res)
		return (NULL);
	vars->res[0] = '\0';
	vars->k = 0;
	vars->i = 0;
	while (s[vars->i])
	{
		vars->j = 0;
		if (s[vars->i] == '$' && s[vars->i + 1] != ' '
			&& s[vars->i + 1] && !ft_isdigit(s[vars->i + 1]))
			here_doc_expand_norm(vars, s, env);
		else
			here_doc_expand_norm_two(vars, s, env);
		if (vars->res[vars->k])
			vars->k++;
		if (s[vars->i])
			vars->i++;
		vars->res[vars->k] = '\0';
	}
	return (vars->res);
}

int	ft_here_doc_count(t_token *token)
{
	t_token	*n;
	int		count;

	n = token;
	count = 0;
	while (n)
	{
		if (n->type == DELIMITER)
			count++;
		n = n->next;
	}
	if (count > 16)
		return (0);
	count = 1;
	return (count);
}

t_token	*child_process_for_heredoc(t_token *token, t_env *env, int file)
{
	char	*s;
	char	*new;

	while (1)
	{
		signal(SIGINT, SIG_DFL);
		signal_for_heredoc();
		s = readline("> ");
		if (!s)
			break ;
		if (ft_strcmp(s, token->content) == 0)
			break ;
		new = here_doc_expand(s, env);
		if (!new)
			return (NULL);
		ft_putendl_fd(new, file);
	}
	close(token->fd[1]);
	exit(0);
}

int	here_doc_mininorm(t_token *token)
{
	if (!ft_here_doc_count(token))
	{
		perror("bash: maximum here-document count exceeded");
		return (-1);
	}
	if (pipe(token->fd) == -1)
		return (-1);
	return (token->fd[1]);
}

t_token	*here_doc_implement(t_token *token, t_token *node, t_env *env)
{
	int		file;
	pid_t	id;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	file = here_doc_mininorm(token);
	if (file < 0)
		return (NULL);
	id = fork();
	if (id == -1)
		return (NULL);
	else if (id == 0)
		child_process_for_heredoc(token, env, file);
	close(token->fd[1]);
	wait(&exit_status);
	node->input_file = token->fd[0];
	if (node->input_file == -1)
	{
		printf("bash: %s: No such file or directory\n", token->content);
		return (NULL);
	}
	return (token);
}
