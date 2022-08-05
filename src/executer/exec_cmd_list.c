/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:19:09 by nprimo            #+#    #+#             */
/*   Updated: 2022/08/05 09:33:15 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd_list(t_shell *sh)
{
	t_list	*head;
	t_cmd	*cmd;

	head = sh->cmd_list;
	while (head)
	{
		cmd = (t_cmd *) head->content;
		if (cmd->exec)
		{
			if (exec_cmd(cmd, sh))
				return (sh->exit_status);
		}
		else
		{
			close_cmd_fd(cmd);
			sh->exit_status = 1;
		}
		head = head->next;
	}
	if (ft_lstsize(sh->cmd_list) == 1
		&& is_builitin(((t_cmd *) sh->cmd_list->content)->av[0]) >= 0)
		return (sh->exit_status);
	while (wait(&sh->exit_status) != -1)
		;
	return (WEXITSTATUS(sh->exit_status));
}
