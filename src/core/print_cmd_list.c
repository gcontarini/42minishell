/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:10:51 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/29 15:53:36 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_av(char **av);

void	print_cmd_list(t_list *cmd_list)
{
	t_list	*head;
	t_cmd	*cmd;

	head = cmd_list;
	while (head)
	{
		printf("av: ");
		cmd = (t_cmd*) head->content;
		print_av(cmd->av);
		head = head->next;
	}
}

static void	print_av(char **av)
{
	int pos;

	pos = 0;
	while (av && av[pos])
	{
		printf("%s\n", av[pos]);
		pos++;
	}
}