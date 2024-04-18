/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_norm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:44:23 by ousabbar          #+#    #+#             */
/*   Updated: 2024/04/18 08:48:11 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	pipe_error(t_token *s)
{
	if (!s->next)
		return (0);
	if (!s->prev)
		return (0);
	if (s->prev->type != CMD && s->prev->type != FILE_OUT
		&& s->prev->type != FILE_IN && s->prev->type != FILE_APP
		&& s->prev->type != DELIMITER)
		return (0);
	if (s->next->type != CMD && s->next->type != RED_OUTPUT
		&& s->next->type != DELIMITER && s->next->type != RED_APPEND
		&& s->next->type != RED_INPUT && s->next->type != HERE_DOC)
		return (0);
	return (1);
}

int	red_output_error(t_token *s)
{
	if (!s->next)
		return (0);
	if (!s->prev)
		return (1);
	if (s->prev)
		if (s->prev->type != CMD && s->prev->type != FILE_OUT
			&& s->prev->type != PIPE && s->prev->type != FILE_IN
			&& s->prev->type != FILE_APP && s->prev->type != DELIMITER)
			return (0);
	if (s->next->type != FILE_OUT)
		return (0);
	return (1);
}

int	red_input_error(t_token *s)
{
	if (!s->next)
		return (0);
	if (!s->prev)
		return (1);
	if (s->prev)
	{
		if (s->prev->type != CMD && s->prev->type != FILE_OUT
			&& s->prev->type != PIPE && s->prev->type != FILE_IN
			&& s->prev->type != FILE_APP && s->prev->type != DELIMITER)
			return (0);
	}
	if (s->next->type != FILE_IN)
		return (0);
	return (1);
}

int	red_append_error(t_token *s)
{
	if (!s->next)
		return (0);
	if (!s->prev)
		return (1);
	if (s->prev)
		if (s->prev->type != CMD && s->prev->type != FILE_OUT
			&& s->prev->type != PIPE && s->prev->type != FILE_IN
			&& s->prev->type != FILE_APP && s->prev->type != DELIMITER)
			return (0);
	if (s->next->type != FILE_APP)
		return (0);
	return (1);
}
