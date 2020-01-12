/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:14:46 by jsance            #+#    #+#             */
/*   Updated: 2019/09/13 09:33:08 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_last(t_list *begin_list)
{
	t_list	*last;

	last = begin_list;
	if (!last)
		return (0);
	while (last->next)
		last = last->next;
	return (last);
}
