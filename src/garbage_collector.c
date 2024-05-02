/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:05:46 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/01 20:06:06 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*ft_malloc(size_t	size, t_free **alloc, void *mem)
{
	t_free	*new;

	new = (t_free *)malloc(sizeof(t_free));
	if (!new)
		return (NULL);
	if (!mem)
		new->mem = malloc(size);
	else
		new->mem = mem;
	if (!(new->mem))
		return (free(new), NULL);
	add_front_mem(alloc, new);
	return (new->mem);
}

void	add_front_mem(t_free **alloc, t_free *new)
{
	new->next = *alloc;
	*alloc = new;
}

void	garbage_collector(t_free **alloc)
{
	t_free	*holder;

	holder = *alloc;
	while (holder)
	{
		free(holder->mem);
		holder = holder->next;
	}
	free(*alloc);
	*alloc = NULL;
}
