/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comm_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:59:38 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/28 17:20:42 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_comm_list	*get_comm_list(char *input)
{
	t_comm_list	*comm_list;
	t_list		*token_list;
	int			pos;

	token_list = NULL;
	get_token_list(input, &token_list); // need to add a check if it fails
	// need to check how many command are there (count_comm or something like that)
	comm_list = malloc(sizeof(t_comm_list) * 1); // number of commands instead of 1
	// while loop to assign all the commands
	comm_list->av = malloc(sizeof(comm_list->av) * (ft_lstsize(token_list) + 1));
	pos = 0;
	while (token_list)
	{
		comm_list->av[pos] = token_list->content;
		token_list = token_list->next;
		pos++;
	}
	comm_list->in.fname = NULL;
	comm_list->out.fname = NULL;
	comm_list->next = NULL;
	return (comm_list);
}