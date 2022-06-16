/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:19:09 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/16 14:30:51 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd_list(t_list *cmd_list)
{
	t_list	*head;
	t_cmd	*cmd;

	head = cmd_list;
	while (head)
	{
		cmd = (t_cmd *) head->content;
		if (exec_cmd(*cmd, NULL))
			return (1);
		head = head->next;
	}
	while (wait(NULL) != -1)
		;
	// head = cmd_list;
	// while (head)
	// {
	// 	cmd = (t_cmd *) head->content;
	// 	waitpid(cmd->pid, NULL, 0);
	// 	head = head->next;
	// }
	return (0);
}
