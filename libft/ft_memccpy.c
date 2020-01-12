/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:09:47 by jsance            #+#    #+#             */
/*   Updated: 2019/09/15 11:03:03 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	s1 = (unsigned char *)src;
	s2 = (unsigned char *)dst;
	while (i < n)
	{
		s2[i] = s1[i];
		if (s1[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (0);
}
