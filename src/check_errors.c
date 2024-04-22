/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:33:54 by ousabbar          #+#    #+#             */
/*   Updated: 2024/04/21 18:07:55 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


t_token	*ft_check_errors(t_token *token)
{
	if (!syntax_error(token))
	{
		ft_putendl_fd("syntax error", 2);
		exit_status = 258 << 8;
		return (NULL);
	}
	return (token);
}
