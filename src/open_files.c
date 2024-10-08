/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 06:59:16 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 14:37:47 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*file_out(t_token *token, t_token *node)
{
	node->output_file = open(token->content,
			O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (node->output_file == -1)
	{
		node->output_file = -2;
		perror("mini");
		return (NULL);
	}
	return (token);
}

t_token	*file_append(t_token *token, t_token *node)
{
	node->output_file = open(token->content,
			O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (node->output_file == -1)
	{
		node->output_file = -2;
		perror("mini");
		return (NULL);
	}
	return (token);
}

t_token	*file_input(t_token *token, t_token *node)
{
	if (token->type == FILE_IN)
	{
		if (access(token->content, F_OK | R_OK) == -1)
		{
			node->exit_status = 1;
			g_exit_status = 1;
		}
		node->input_file = open(token->content, O_RDONLY);
		if (node->input_file == -1)
		{
			node->input_file = -2;
			printf("mini: %s: No such file or directory\n", token->content);
			return (token);
		}
	}
	return (token);
}

t_token	*ft_openning_files(t_token *token, t_token *node)
{
	if (token->type == FILE_OUT && node->exit_status != (1))
	{
		if (!file_out(token, node))
			return (NULL);
	}
	else if (token->type == FILE_IN)
	{
		if (!file_input(token, node))
			return (NULL);
	}
	else if (token->type == FILE_APP && node->exit_status != (1))
	{
		if (!file_append(token, node))
			return (NULL);
	}
	return (token);
}
