/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:21:43 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/31 16:04:34 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *cmd, t_shell *sh)
{
	int		n_flag;
	int		pos;

	(void) sh;
	n_flag = 0;
	pos = 1;
	if (cmd->av[pos] && ft_strncmp(cmd->av[pos], "-n", 3) == 0)
	{
		n_flag = 1;
		pos += 1;
	}
	while (cmd->av[pos])
	{
		write(cmd->out.fd, cmd->av[pos], ft_strlen(cmd->av[pos]));
		pos++;
		if (cmd->av[pos])
			write(cmd->out.fd, " ", 1);
	}
	if (n_flag == 0)
		write(cmd->out.fd, "\n", 1);
	return (0);
}
