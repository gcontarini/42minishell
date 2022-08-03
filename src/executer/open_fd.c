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

static int	get_fd_in(t_list *cmd_list, t_shell *sh);
static int	get_fd_out(t_list *cmd_list, t_shell *sh);
static void	open_empty_pipe(t_list *cmd_list, t_shell *sh);

int	open_fd(t_list *cmd_list, t_shell *sh)
{
	t_list	*curr_cmd;

	curr_cmd = cmd_list;
	while (curr_cmd)
	{
		if (get_fd_in(curr_cmd, sh)
			|| get_fd_out(curr_cmd, sh))
			return (1);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}

static int	get_fd_in(t_list *cmd_list, t_shell *sh)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) cmd_list->content;
	if (!cmd->in.fname && cmd->in.fd < 0)
		cmd->in.fd = STDIN_FILENO;
	else if (cmd->in.fname && ft_strncmp("<", cmd->in.red, 2) == 0)
		cmd->in.fd = open(cmd->in.fname, O_RDONLY);
	else if (cmd->in.fname && ft_strncmp("<<", cmd->in.red, 2) == 0)
		cmd->in.fd = here_doc(cmd->in.fname, sh);
	return (ofile_checker(cmd->in.fd, sh));
}

static void	open_empty_pipe(t_list *cmd_list, t_shell *sh)
{
	t_cmd	*next_cmd;
	int		fd_pipe[2];

	if (cmd_list->next)
	{
		next_cmd = (t_cmd *) cmd_list->next->content;
		error_check(pipe(fd_pipe), sh);
		next_cmd->in.fd = fd_pipe[0];
		close(fd_pipe[1]);
	}
}

static int	get_fd_out(t_list *cmd_list, t_shell *sh)
{
	int		fd_pipe[2];
	t_cmd	*cmd;
	t_cmd	*next_cmd;

	cmd = (t_cmd *) cmd_list->content;
	if (!cmd->out.red && cmd->out.fd < 0)
		cmd->out.fd = STDOUT_FILENO;
	else if (ft_strncmp(cmd->out.red, "|", 2) == 0)
	{
		if (cmd_list->next)
		{
			next_cmd = (t_cmd *) cmd_list->next->content;
			error_check(pipe(fd_pipe), sh); // Change this? yes
			next_cmd->in.fd = fd_pipe[0];
			cmd->out.fd = fd_pipe[1];
		}
	}
	else if (ft_strncmp(">", cmd->out.red, 2) == 0)
		cmd->out.fd = open(cmd->out.fname, O_WRONLY | O_CREAT | O_TRUNC, 0622);
	else if (ft_strncmp(">>", cmd->out.red, 3) == 0)
		cmd->out.fd = open(cmd->out.fname, O_WRONLY | O_APPEND | O_CREAT, 0622);
	if (cmd->pipe == true && ft_strncmp("|", cmd->out.red, 2) != 0)
		open_empty_pipe(cmd_list, sh);
	return (ofile_checker(cmd->out.fd, sh));
}
