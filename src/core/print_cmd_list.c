/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:10:51 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/25 15:37:54 by nprimo           ###   ########.fr       */
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
		cmd = (t_cmd *) head->content;
		printf("av: \n");
		print_av(cmd->av);
		printf("\n");
		printf("file in: %s\nred: %s\nfd: %d\n", cmd->in.fname,
			cmd->in.redirection, cmd->in.fd);
		printf("\n");
		printf("file out: %s\nred: %s\nfd: %d\n", cmd->out.fname,
			cmd->out.redirection, cmd->out.fd);
		head = head->next;
		printf("---\n");
	}
}

static void	print_av(char **av)
{
	int	pos;

	pos = 0;
	while (av && av[pos])
	{
		printf(" %s ", av[pos]);
		pos++;
	}
}
