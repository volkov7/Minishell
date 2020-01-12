/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:39:20 by jsance            #+#    #+#             */
/*   Updated: 2019/09/12 17:10:36 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s2;
	unsigned char	*s1;

	if (dst == NULL && src == NULL)
		return (NULL);
	s1 = (unsigned char	*)src;
	s2 = (unsigned char	*)dst;
	i = 0;
	while (i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	return (dst);
}
