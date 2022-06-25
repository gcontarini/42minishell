/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_to_av.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:02:05 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/25 15:41:30 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**llist_to_av(t_list *llist)
{
	char	**av;
	t_list	*head;
	int		pos;

	av = (char **)error_check_pointer(malloc(sizeof(char *)
				* (ft_lstsize(llist) + 1)));
	head = llist;
	pos = 0;
	while (head)
	{
		av[pos] = (char *) head->content;
		head = head->next;
		pos++;
	}
	av[pos] = NULL;
	return (av);
}
