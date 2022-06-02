/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:48:50 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/02 14:51:08 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_pos(t_list **list, int pos, void (*del)(void *))
{
	t_list	*prev_el;
	t_list	*next_el;
	t_list	*head;

	if (!list)
		return ;
	head = *list;
	if (pos == 0)
	{
		*list = (*list)->next;
		pos--;
		ft_lstdelone(head, del);
	}
	while (head && pos > 0)
	{
		prev_el = head;
		if (head->next)
			next_el = head->next->next;
		pos--;
		head = head->next;
	}
	if (pos == 0)
	{
		prev_el->next = next_el;
		ft_lstdelone(head, del);
	}
}
