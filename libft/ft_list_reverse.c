/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:20:12 by jsance            #+#    #+#             */
/*   Updated: 2019/09/18 17:37:59 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_reverse(t_list **begin_list)
{
	t_list	*next;
	t_list	*cur;
	t_list	*last;

	if (begin_list && *begin_list)
	{
		next = 0;
		last = 0;
		cur = *begin_list;
		while (cur)
		{
			next = cur->next;
			cur->next = last;
			last = cur;
			cur = next;
		}
		*begin_list = last;
	}
}
