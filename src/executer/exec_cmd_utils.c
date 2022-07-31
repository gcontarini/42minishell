/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:21:27 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/31 18:48:10 by gcontari         ###   ########.fr       */
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
