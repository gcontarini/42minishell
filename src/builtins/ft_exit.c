/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:11:28 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/31 16:05:02 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERORR_AC "bash: exit: too many arguments\n"

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
			{
				ft_putstr_fd(ERORR_AC, 2);
				return (1);
			}
			sh->exit_status = ft_atoi(cmd->av[1]);
			free_shell(sh);
			exit(sh->exit_status);
		}
		else
		{
			ft_putstr_fd("bash:exit: ", 2);
			ft_putstr_fd(cmd->av[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_shell(sh);
			exit(2);
		}
	}
	free_shell(sh);
	exit(sh->exit_status);
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
