/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:19:09 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/02 12:19:20 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_fd_in(t_cmd	cmd);
static int	get_fd_out(t_cmd cmd);

int exec_cmd_list(t_list *cmd_list)
{
	t_list  *head;
	t_cmd	*cmd;

	head = cmd_list;
	while (head)
	{
		cmd = (t_cmd *) (head->content);
		cmd->in.fd = get_fd_in(*cmd);
		cmd->out.fd = get_fd_out(*cmd);
		if (cmd->out.fd == - 1 || cmd->in.fd == -1)
			return (1);
		if (exec_cmd(*cmd, NULL))
			return (1);
		head = head->next;
	}
	return (0);
}

static int	get_fd_in(t_cmd cmd)
{
	int	fd;

	if (!cmd.in.fname)
			fd = STDIN_FILENO;
	else
	{
		fd = open(cmd.in.fname, O_RDONLY);
		if (fd == -1)
			return (-1);
	}
	return (fd);
}

static int	get_fd_out(t_cmd cmd)
{
	int	fd;

	if (!cmd.in.fname)
			fd = STDOUT_FILENO;
	else
	{
		fd = open(cmd.in.fname, O_WRONLY | O_CREAT);
		if (fd == -1)
			return (-1);
	}
	return (fd);
}
