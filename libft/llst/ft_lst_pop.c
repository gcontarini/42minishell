/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_pop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:32:00 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/06 11:32:44 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_pop(t_list **llist, void *content)
{
	t_list	*prev_el;
	t_list	*head;

	head = *llist;
	prev_el = head;
	while (head)
	{
		if (head->content == content)
		{
			if (head == prev_el)
				*llist = (*llist)->next;
			else if (head->next)
				prev_el->next = head->next;
			else
				prev_el->next = NULL;
			head->next = NULL;
			return (head);
		}
		prev_el = head;
		head = head->next;
	}
	return (NULL);
}
