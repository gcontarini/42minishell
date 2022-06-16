/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 09:58:42 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/16 15:41:28 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(void	*cmd_void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) cmd_void;
	ft_lstclear(&cmd->token_list, NULL);
	if (cmd->av)
		free_split(cmd->av);
	if (cmd->in.fname)
		free(cmd->in.fname);
	if (cmd->out.fname)
		free(cmd->out.fname);
	if (cmd->in.redirection)
		free(cmd->in.redirection);
	if (cmd->out.redirection)
		free(cmd->out.redirection);
}
