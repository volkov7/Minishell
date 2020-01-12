/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:21:03 by jsance            #+#    #+#             */
/*   Updated: 2019/09/12 18:24:18 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	if (size == SIZE_MAX)
		return (NULL);
	str = (char*)malloc(sizeof(*str) * size + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, size);
	str[size] = '\0';
	return (str);
}
