/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:06:36 by ousabbar          #+#    #+#             */
/*   Updated: 2024/04/21 16:17:32 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_token	*file_out(t_token *token, t_token *node)
{
	node->output_file = open(token->content,
			O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (node->output_file == -1)
	{
		perror("mini");
		return (NULL);
	}
	return (token);
}
t_token *file_append(t_token *token, t_token *node)
{
	node->output_file = open(token->content,
			O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (node->output_file == -1)
	{
		perror("mini");
		return (NULL);
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
		if (access(token->content, F_OK | R_OK) == -1)
		{
			node->exit_status = 1;
			exit_status = 1 << 8;
		}	
		node->input_file = open(token->content, O_RDONLY);
		if (node->input_file == -1)
		{
			printf("bash: %s: No such file or directory\n", token->content);
			return (token);
		}
	}
	else if (token->type == FILE_APP && node->exit_status != (1))
	{
		if (!file_append(token, node))
			return (NULL);
	}
	return (token);
}
