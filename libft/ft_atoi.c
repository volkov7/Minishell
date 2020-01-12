/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:38:00 by jsance            #+#    #+#             */
/*   Updated: 2019/09/15 10:18:41 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long int	test_max(unsigned long long int res, int sign)
{
	if (res > 9223372036854775807)
		return (sign == 1 ? -1 : 0);
	else
		return (res * sign);
}

int								ft_atoi(const char *str)
{
	unsigned long long int	res;
	int						sign;

	res = 0;
	sign = 1;
	while ((*str >= 0 && *str < 27) || (*str > 27 && *str <= 32))
		str++;
	if (!(*str))
		return (0);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (test_max(res, sign));
}
