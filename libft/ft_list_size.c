/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:56:49 by jsance            #+#    #+#             */
/*   Updated: 2019/09/11 18:01:26 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_list_size(t_list *begin_list)
{
	int		count;
	t_list	*s;

	count = 0;
	s = begin_list;
	while (s)
	{
		count++;
		s = s->next;
	}
	return (count);
}
