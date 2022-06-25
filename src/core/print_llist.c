/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_llist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:00:02 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/01 10:07:49 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_llist(t_list *llist)
{
	t_list	*head;

	head = llist;
	while (head)
	{
		printf(" %s ", (char *) head->content);
		head = head->next;
	}
	printf("\n");
}
