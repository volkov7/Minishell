/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 16:49:55 by jsance            #+#    #+#             */
/*   Updated: 2019/09/13 09:30:14 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;
	t_list	*curr;

	if (alst && del)
	{
		curr = *alst;
		while (curr)
		{
			next = curr->next;
			del(curr->content, curr->content_size);
			free(curr);
			curr = next;
		}
		*alst = NULL;
	}
}
