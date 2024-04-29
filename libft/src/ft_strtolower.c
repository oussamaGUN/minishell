/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:46:27 by melfersi          #+#    #+#             */
/*   Updated: 2024/04/29 11:47:05 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char	*ft_strtolower(char *str)
{
	while (*str)
	{
		*str = ft_tolower(*str);
		str++;
	}
	return (str);
}
