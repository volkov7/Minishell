/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 13:18:50 by jsance            #+#    #+#             */
/*   Updated: 2019/09/11 15:35:41 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	start;
	unsigned int	end;

	if (s == NULL)
		return (NULL);
	if (!(*s))
		return (ft_strnew(0));
	start = 0;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	end = ft_strlen(s);
	while ((s[end - 1] == ' ' || s[end - 1] == '\n' || s[end - 1] == '\t') &&
			(start < end))
		end--;
	return (ft_strsub(s, start, end - start));
}
