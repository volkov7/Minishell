/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 10:43:17 by jsance            #+#    #+#             */
/*   Updated: 2019/09/07 19:43:56 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*found;

	if ((char)c == '\0' && *str == '\0')
		return ((char *)str);
	found = 0;
	while (*str != '\0')
	{
		if (*str == (char)c)
			found = str;
		str++;
		if ((char)c == '\0' && *str == '\0')
			return ((char*)str);
	}
	return ((char *)found);
}
