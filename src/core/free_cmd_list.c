/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 09:58:42 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/06 17:50:42 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(t_list **cmd_list)
{
	t_list	*curr_cmd;
	t_cmd	*cmd;

	curr_cmd = *cmd_list;
	while (curr_cmd)
	{
		cmd = (t_cmd *) curr_cmd->content;
		if (cmd->in.fname)
			free(cmd->in.fname);
		if (cmd->out.fname)
			free(cmd->out.fname);
		free_split(cmd->av);
		ft_lstclear(&cmd->token_list, free);
		curr_cmd = curr_cmd->next;
		free(cmd);
	}
	free(*cmd_list);
}
