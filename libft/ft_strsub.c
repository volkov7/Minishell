/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 12:29:45 by jsance            #+#    #+#             */
/*   Updated: 2019/09/12 16:25:43 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*fresh;
	size_t	i;

	if (!s)
		return (NULL);
	if (!(fresh = (char*)malloc(sizeof(*fresh) * len + 1)))
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		fresh[i] = s[start];
		i++;
		start++;
	}
	fresh[i] = '\0';
	return (fresh);
}
