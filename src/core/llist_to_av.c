/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_to_av.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:02:05 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/01 20:34:03 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**llist_to_av(t_list *llist, t_shell sh)
{
	char	**av;
	t_list	*head;
	int		pos;

	av = (char **)xmc(malloc(sizeof(char *)
				* (ft_lstsize(llist) + 1)), NULL, 0, sh);
	head = llist;
	pos = 0;
	while (head)
	{
		av[pos] = ((t_token *) head->content)->s;
		head = head->next;
		pos++;
	}
	av[pos] = NULL;
	return (av);
}
