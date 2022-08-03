/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:11:28 by nprimo            #+#    #+#             */
/*   Updated: 2022/08/03 20:31:45 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_ac(char **av);
static int	is_all_digit(char *str);

int	ft_exit(t_cmd *cmd, t_shell *sh)
{
	cmd = (void *) cmd;
	if (get_ac(cmd->av) >= 2)
	{
		if (is_all_digit(cmd->av[1]))
		{
			if (get_ac(cmd->av) > 2)
				return (ms_exit(1, ERRMSG_EXIT, false, sh));
			sh->exit_status = (char) ft_atoi(cmd->av[1]);
			ms_exit(sh->exit_status, NULL, true, sh);
		}
		else
			ms_exit(2, ERRMSG_EXIT2, true, sh);
	}
	return (ms_exit(sh->exit_status, NULL, true, sh)); // return last exit status
}

static int	is_all_digit(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
