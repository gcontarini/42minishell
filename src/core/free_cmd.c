/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 09:58:42 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/02 10:12:56 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(void *void_cmd)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) void_cmd;
	if (cmd->in.fname)
		free(cmd->in.fname);
	if (cmd->out.fname)
		free(cmd->out.fname);
	free_split(cmd->av);
	free(cmd);
}
