/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:33:54 by ousabbar          #+#    #+#             */
/*   Updated: 2024/04/18 10:23:37 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_token	*ft_check_errors(t_token *token)
{
	int	flag;

	flag = syntax_error(token);
	if (flag == 0)
	{
		ft_putendl_fd("syntax error", 2);
		exit_status = 258 << 8;
		return (NULL);
	}
	else if (flag == 2)
		return (NULL);
	return (token);
}
