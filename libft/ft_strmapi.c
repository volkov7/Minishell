/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:24:41 by jsance            #+#    #+#             */
/*   Updated: 2019/09/10 09:02:48 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fresh;
	unsigned int	index;

	if (s && f)
	{
		index = 0;
		fresh = (char*)malloc(sizeof(*fresh) * ft_strlen(s) + 1);
		if (!fresh)
			return (NULL);
		while (s[index] != '\0')
		{
			fresh[index] = f(index, s[index]);
			index++;
		}
		fresh[index] = '\0';
		return (fresh);
	}
	return (NULL);
}
