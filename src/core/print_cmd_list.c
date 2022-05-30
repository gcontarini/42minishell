/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:10:51 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/30 17:37:24 by nprimo           ###   ########.fr       */
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
		printf("av: \n");
		cmd = (t_cmd*) head->content;
		print_av(cmd->av);
		printf("\n");
		printf("token list: \n");
		print_llist(cmd->token_list);
		printf("\n");
		printf("file in:\n%s\n", cmd->in.fname);
		printf("file out:\n%s\n", cmd->out.fname);
		head = head->next;
		printf("---\n");
	}
}

static void	print_av(char **av)
{
	int pos;

	pos = 0;
	while (av && av[pos])
	{
		printf(" %s ", av[pos]);
		pos++;
	}
}
