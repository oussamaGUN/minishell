/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:24:54 by ousabbar          #+#    #+#             */
/*   Updated: 2023/10/31 18:24:56 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*s;
	size_t		len;
	size_t		len1;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s2);
	len = ft_strlen(s1);
	s = (char *)malloc(sizeof(char) * (len + len1 + 1));
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (j < len)
		s[i++] = s1[j++];
	j = 0;
	while (j < len1)
		s[i++] = s2[j++];
	s[i] = '\0';
	return (s);
}
