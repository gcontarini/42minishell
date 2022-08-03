/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:21:27 by nprimo            #+#    #+#             */
/*   Updated: 2022/08/03 19:48:35 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_cmd_fd(t_cmd *cmd)
{
	if (cmd->in.fd != STDIN_FILENO)
		close(cmd->in.fd);
	if (cmd->out.fd != STDOUT_FILENO)
		close(cmd->out.fd);
}

int	is_builitin(char *str)
{
	static char	*builtin_list[] = {
		"echo", "env", "export", "exit", "pwd", "unset", "cd", NULL};
	int			pos;

	pos = 0;
	while (builtin_list[pos])
	{
		if (ft_strncmp(builtin_list[pos], str,
				ft_strlen(builtin_list[pos]) + 1) == 0)
			return (pos);
		pos++;
	}
	return (-1);
}

int	ms_redirect(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1
			|| close(fd_in) == -1)
			return (-1);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1
			|| close(fd_out) == -1)
			return (-1);
	}
	return (0);
}
