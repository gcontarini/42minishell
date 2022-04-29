/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comm_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:59:38 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/29 12:27:57 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_comm_list(char *input)
{
	t_cmd	*comm_list; // need to be dynamic allocation
	t_list	*token_list;
	int		pos;

	token_list = NULL;
	get_token_list(input, &token_list); // need to add a check if it fails
	// need to check how many command are there (count_comm or something like that)
	// while loop to assign all the commands
	comm_list = malloc(sizeof(t_cmd) * 2);
	comm_list[0].av = malloc(sizeof(comm_list[0].av) * (ft_lstsize(token_list) + 1));
	pos = 0;
	while (token_list)
	{
		comm_list[0].av[pos] = token_list->content;
		token_list = token_list->next;
		pos++;
	}
	comm_list[0].av[pos] = NULL;
	comm_list[0].in.fname = NULL;
	comm_list[0].out.fname = NULL;
	comm_list[1].av = NULL;
	return (comm_list);
}