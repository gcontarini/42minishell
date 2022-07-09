/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:21:27 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/08 17:22:11 by nprimo           ###   ########.fr       */
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
