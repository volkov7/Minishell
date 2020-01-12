/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 09:16:01 by jsance            #+#    #+#             */
/*   Updated: 2019/09/07 14:15:11 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	k;

	if (!(*needle))
		return ((char *)haystack);
	while (*haystack != '\0' && len)
	{
		if (*haystack == *needle)
		{
			k = 0;
			while (*haystack == needle[k] && len - k > 0)
			{
				haystack++;
				k++;
				if (needle[k] == '\0')
					return ((char *)(haystack - k));
			}
			haystack = haystack - k;
		}
		haystack++;
		len--;
	}
	return (0);
}
