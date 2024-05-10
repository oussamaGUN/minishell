/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:55:37 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:16:17 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dash_n(char *s)
{
	if (!s)
		return (0);
	if (*s != '-' || *(s + 1) != 'n')
		return (0);
	s++;
	while (*s)
		if (*s++ != 'n')
			return (0);
	return (1);
}

int	echo(t_token *lst)
{
	if (!(*++(lst->arr)))
		printf("\n");
	else if (check_dash_n(*(lst->arr)++))
	{
		while (check_dash_n(*(lst->arr)))
			lst->arr++;
		while (*(lst->arr))
		{
			ft_putstr_fd(*(lst->arr)++, 1);
			if (*(lst->arr))
				ft_putchar_fd(' ', 1);
		}
	}
	else
	{
		(lst->arr)--;
		while (*(lst->arr))
		{
			ft_putstr_fd(*(lst->arr)++, STDOUT_FILENO);
			if (*(lst->arr))
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (0);
}
