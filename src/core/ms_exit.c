/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:14:41 by gcontarini        #+#    #+#             */
/*   Updated: 2022/08/03 19:58:20 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exit(int status, char *err_msg, bool is_exit, t_shell *sh)
{
	if (err_msg)
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	if (sh)
		sh->exit_status = status;
	if (is_exit)
	{
		if (sh)
			free_shell(sh);
		exit(status);
	}
	return (status);
}
