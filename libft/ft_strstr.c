/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 11:24:45 by jsance            #+#    #+#             */
/*   Updated: 2019/09/07 10:20:09 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		k;

	if (!(*needle))
		return ((char *)haystack);
	while (*haystack != '\0')
	{
		if (*haystack == *needle)
		{
			k = 0;
			while (*haystack == needle[k])
			{
				haystack++;
				k++;
				if (needle[k] == '\0')
					return ((char *)(haystack - k));
			}
			haystack = haystack - k;
		}
		haystack++;
	}
	return (0);
}
