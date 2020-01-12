/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 12:51:07 by jsance            #+#    #+#             */
/*   Updated: 2019/09/14 10:10:05 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*f;

	if (!s1 || !s2)
		return (NULL);
	if (ft_strlen(s1) + ft_strlen(s2) == SIZE_MAX)
		return (NULL);
	f = (char*)malloc(sizeof(*f) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!f)
		return (NULL);
	ft_strcpy(f, s1);
	ft_strcat(f, s2);
	return (f);
}
