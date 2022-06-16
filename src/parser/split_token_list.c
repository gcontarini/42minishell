/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:37:34 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/16 17:46:20 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*split_token_list(t_list **token_list)
{
	t_list	*curr_head;
	t_list	*head;

	curr_head = *token_list;
	head = curr_head;
	while (head)
	{
		if (is_control_operator(head->content))
			break ;
		head = head->next;
	}
	if (head)
	{
		*token_list = head->next;
		head->next = NULL;
	}
	return (curr_head);
}