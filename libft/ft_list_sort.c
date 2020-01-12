/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:24:30 by jsance            #+#    #+#             */
/*   Updated: 2019/09/18 17:34:19 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*s1;
	t_list	*copy;
	t_list	*s2;

	if (begin_list && *begin_list && cmp)
	{
		s1 = *begin_list;
		while (s1)
		{
			s2 = *begin_list;
			while (s2->next)
			{
				if (cmp(s2->content, s2->next->content) > 0)
				{
					copy = s2->content;
					s2->content = s2->next->content;
					s2->next->content = copy;
				}
				else
					s2 = s2->next;
			}
			s1 = s1->next;
		}
	}
}
