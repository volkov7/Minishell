/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:57:39 by jsance            #+#    #+#             */
/*   Updated: 2019/09/15 11:09:54 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	size_t	len;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	len = 0;
	i = 0;
	while (dst[len] != '\0')
		len++;
	while (i < n && *src != '\0')
	{
		dst[len + i] = *src;
		i++;
		src++;
	}
	dst[len + i] = '\0';
	return (dst);
}
