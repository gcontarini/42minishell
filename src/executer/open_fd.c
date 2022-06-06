/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:19:09 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/26 17:54:00 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_fd_in(t_list *cmd_list);
static int	get_fd_out(t_list *cmd_list);

int	open_fd(t_list *cmd_list)
{
	t_list	*curr_cmd;
	t_cmd	*cmd;

	curr_cmd = cmd_list;
	while (curr_cmd)
	{
		cmd = (t_cmd *)curr_cmd->content;
		get_fd_in(curr_cmd);
		get_fd_out(curr_cmd);
		// if (cmd->out.fd == - 1 || cmd->in.fd == -1)
		// 	return (1);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}

static int	get_fd_in(t_list *cmd_list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) cmd_list->content;
	if (!cmd->in.fname && cmd->in.fd < 0)
			cmd->in.fd = STDIN_FILENO;
	else if (cmd->in.fname && ft_strncmp("<", cmd->in.redirection, 2) == 0)
	{
		cmd->in.fd = open(cmd->in.fname, O_RDONLY);
		if (cmd->in.fd == -1)
			return (-1);
	}
	return (0);
}

static int	get_fd_out(t_list *cmd_list)
{
	int		fd_pipe[2];
	t_cmd	*cmd;
	t_cmd	*next_cmd;

	cmd = (t_cmd *) cmd_list->content;
	if (!cmd->out.fname && cmd->out.fd < 0)
			cmd->out.fd = STDOUT_FILENO;
	else if (ft_strncmp(cmd->out.fname, "|", 2) == 0)
	{
		if (cmd_list->next)
		{
			next_cmd = (t_cmd *) cmd_list->next->content;
			error_check(pipe(fd_pipe));
			next_cmd->in.fd = fd_pipe[0];
			cmd->out.fd = fd_pipe[1];
		}
	}
	else if (ft_strncmp(">", cmd->out.redirection, 2) == 0)
	{
		cmd->out.fd = open(cmd->out.fname, O_WRONLY | O_CREAT, 0622);
		if (cmd->out.fd == -1)
			return (-1);
	}
	else if (ft_strncmp(">>", cmd->out.redirection, 3) == 0)
	{
		cmd->out.fd = open(cmd->out.fname, O_APPEND | O_CREAT, 0622);
		if (cmd->out.fd == -1)
			return (-1);
	}
	return (0);
}
