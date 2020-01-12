/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:08:08 by jsance            #+#    #+#             */
/*   Updated: 2019/09/11 18:11:15 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_push_back(t_list **begin_list, void *content,
		size_t content_size)
{
	t_list *s;

	s = *begin_list;
	if (s == 0)
		*begin_list = ft_lstnew(content, content_size);
	else
	{
		while (s->next)
			s = s->next;
		s->next = ft_lstnew(content, content_size);
	}
}
