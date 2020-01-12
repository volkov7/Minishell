/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:01:17 by jsance            #+#    #+#             */
/*   Updated: 2019/09/11 15:01:39 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_nb(int n)
{
	size_t	size;
	size_t	i;

	if (n == -2147483648)
		return (10);
	if (n < 0)
		n = -n;
	if (n == 0)
		return (1);
	size = 1;
	i = 0;
	while (n / size)
	{
		size *= 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char	*fresh;
	int		sign;
	size_t	size;

	sign = (n < 0) ? 1 : 0;
	size = size_nb(n);
	if (!(fresh = ft_strnew(size + sign)))
		return (NULL);
	fresh[size] = '\0';
	if (sign)
		fresh[0] = '-';
	else if (n > 0)
		size--;
	else
		fresh[0] = '0';
	while (n)
	{
		if (n > 0)
			fresh[size] = '0' + (n % 10);
		else
			fresh[size] = '0' - (n % 10);
		size--;
		n /= 10;
	}
	return (fresh);
}
