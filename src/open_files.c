/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:06:36 by ousabbar          #+#    #+#             */
/*   Updated: 2024/04/18 22:38:48 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_token	*ft_openning_files(t_token *token, t_token *node)
{
	if (token->type == FILE_OUT)
	{
		node->output_file = open(token->content,
				O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (node->output_file == -1)
		{
			perror("mini");
			return (NULL);
		}
	}
	else if (token->type == FILE_IN)
	{
		if (access(token->content, F_OK | R_OK) == -1)	
			node->exit_status = 1;
		node->input_file = open(token->content, O_RDONLY);
		if (node->input_file == -1)
		{
			printf("bash: %s: No such file or directory\n", token->content);
			return (token);
		}
	}
	else if (token->type == FILE_APP)
	{
		node->output_file = open(token->content,
				O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (node->output_file == -1)
			return (NULL);
	}
	return (token);
}
