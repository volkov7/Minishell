/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:54:40 by jsance            #+#    #+#             */
/*   Updated: 2019/09/08 18:55:16 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int i;
	int copy;

	i = 1;
	if (n == -2147483648)
	{
		copy = n;
		n++;
	}
	if (n < 0)
	{
		n = -n;
		ft_putchar('-');
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		if (copy == -2147483648)
			ft_putchar('8');
		else
			ft_putnbr(n % 10);
	}
	if (n < 10)
		ft_putchar('0' + n);
}
