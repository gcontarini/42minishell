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

static void	get_fd_in(t_list *cmd_list, t_shell sh);
static void	get_fd_out(t_list *cmd_list, t_shell sh);

int	open_fd(t_list *cmd_list, t_shell sh)
{
	t_list	*curr_cmd;

	curr_cmd = cmd_list;
	while (curr_cmd)
	{
		get_fd_in(curr_cmd, sh);
		get_fd_out(curr_cmd, sh);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}

static void	get_fd_in(t_list *cmd_list, t_shell sh)
{
	t_cmd	*cmd;
	t_dict	*fd_pair;
	t_list	*head_fd_list;

	cmd = (t_cmd *) cmd_list->content;
	head_fd_list = cmd->fd_pair_list;
	while (head_fd_list)
	{
		fd_pair = (t_dict *) head_fd_list->content;
		if (cmd->fd[0] != STDIN_FILENO)
			error_check(close(cmd->fd[0]), sh);
		if (ft_strncmp("<", fd_pair->key, 2) == 0)
			cmd->fd[0] = open(fd_pair->value, O_RDONLY);
		else if (ft_strncmp("<<", fd_pair->key, 3) == 0)
			cmd->fd[0] = here_doc(fd_pair->value);
		head_fd_list = head_fd_list->next;
	}
}

static void	get_fd_out(t_list *cmd_list, t_shell sh)
{
	int		fd_pipe[2];
	t_cmd	*cmd;
	t_list	*head_fd_pair;
	t_dict	*fd_pair;

	cmd = (t_cmd *) cmd_list->content;
	head_fd_pair = cmd->fd_pair_list;
	while (head_fd_pair)
	{
		fd_pair = (t_dict *) head_fd_pair->content;
		if (cmd->fd[1] != STDOUT_FILENO) // && fd_pair->key is not "|"
			error_check(close(cmd->fd[1]), sh);
		if (ft_strncmp(fd_pair->key, "|", 2) == 0)
		{
			if (cmd_list->next)
			{
				error_check(pipe(fd_pipe), sh);
				((t_cmd *) cmd_list->next->content)->fd[0] = fd_pipe[0];
				cmd->fd[1] = fd_pipe[1];
			}
		}
		else if (ft_strncmp(">", fd_pair->key, 2) == 0)
			cmd->fd[1] = open(fd_pair->value, O_WRONLY | O_CREAT | O_TRUNC, 0622);
		else if (ft_strncmp(">>", fd_pair->key, 3) == 0)
			cmd->fd[1] = open(fd_pair->value, O_WRONLY | O_APPEND | O_CREAT, 0622);
		head_fd_pair = head_fd_pair->next;
	}
}
