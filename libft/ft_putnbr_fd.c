/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:22:05 by jsance            #+#    #+#             */
/*   Updated: 2019/09/08 19:25:35 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
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
		ft_putchar_fd('-', fd);
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		if (copy == -2147483648)
			ft_putchar_fd('8', fd);
		else
			ft_putnbr_fd(n % 10, fd);
	}
	if (n < 10)
		ft_putchar_fd('0' + n, fd);
}
