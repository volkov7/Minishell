/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:34:00 by jsance            #+#    #+#             */
/*   Updated: 2019/09/11 13:54:50 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*s1;
	unsigned char		*s2;

	if (dst == NULL && src == NULL)
		return (NULL);
	s1 = src;
	s2 = dst;
	if (dst > src)
	{
		s1 = (const unsigned char*)src + len - 1;
		s2 = (unsigned char*)dst + len - 1;
		while (len-- > 0)
		{
			*s2 = *s1;
			s2--;
			s1--;
		}
	}
	else
		while (len-- > 0)
			*s2++ = *s1++;
	return (dst);
}
