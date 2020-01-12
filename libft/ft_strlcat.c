/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 09:44:37 by jsance            #+#    #+#             */
/*   Updated: 2019/09/10 08:39:55 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		sum_len;
	const char	*s1;

	if (size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	i = 0;
	s1 = src;
	while ((dst[i] != '\0') && i < size - 1)
		i++;
	sum_len = ft_strlen(dst) + ft_strlen(src);
	while (*s1 != '\0' && i < size - 1)
	{
		dst[i] = *s1++;
		i++;
	}
	dst[i] = '\0';
	return (sum_len);
}
