/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:21:27 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/17 20:20:31 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_cmd_fd(t_cmd *cmd)
{
	if (cmd->fd[0] != STDIN_FILENO)
		close(cmd->fd[0]);
	if (cmd->fd[1] != STDOUT_FILENO)
		close(cmd->fd[1]);
}
