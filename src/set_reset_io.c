/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_reset_io.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:06:06 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:16:17 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_io(t_token *lst)
{
	if (lst->input_file == (-2) || lst->output_file == (-2))
		return (-2);
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
	return (0);
}

int	reset_io(t_token *lst)
{
	dup2(lst->fd[0], STDIN_FILENO);
	dup2(lst->fd[1], STDOUT_FILENO);
	close(lst->fd[0]);
	close(lst->fd[1]);
	return (0);
}
