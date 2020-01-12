/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:01:13 by jsance            #+#    #+#             */
/*   Updated: 2019/09/11 15:03:15 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*fresh;
	unsigned int	i;

	i = 0;
	if (s && f)
	{
		if (!(fresh = (char*)malloc(sizeof(*fresh) * ft_strlen(s) + 1)))
			return (NULL);
		while (s[i] != '\0')
		{
			fresh[i] = f(s[i]);
			i++;
		}
		fresh[i] = '\0';
		return (fresh);
	}
	return (NULL);
}
