/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:26:29 by jsance            #+#    #+#             */
/*   Updated: 2019/09/13 09:27:07 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	clean(t_list **begin)
{
	t_list	*copy;

	while (*begin)
	{
		copy = (*begin)->next;
		free(*begin);
		*begin = copy;
	}
	*begin = NULL;
}

static int	iterate(t_list **lst, t_list **curr, t_list **new,
							t_list *(*f)(t_list *elem))
{
	while (*lst)
	{
		if (!(*new = (t_list*)malloc(sizeof(t_list))))
		{
			return (1);
			break ;
		}
		*new = f(*lst);
		(*curr)->next = *new;
		(*curr) = (*curr)->next;
		*lst = (*lst)->next;
	}
	return (0);
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*begin;
	t_list	*new;
	t_list	*curr;

	if (lst && f)
	{
		if (!(curr = (t_list*)malloc(sizeof(t_list))))
			return (NULL);
		curr = f(lst);
		begin = curr;
		lst = lst->next;
		if (iterate(&lst, &curr, &new, f))
			clean(&begin);
	}
	else
		return (NULL);
	return (begin);
}
