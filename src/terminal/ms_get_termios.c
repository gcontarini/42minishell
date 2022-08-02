/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_termios.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:44:23 by gcontari          #+#    #+#             */
/*   Updated: 2022/08/02 09:04:37 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_term	ms_get_termios(t_shell *sh)
{
	t_term	curr_term;

	if (isatty(sh->term_fd) == 0)
	{
		free_shell(sh);
		ms_exit(INVALID_TERM, ERRMSG_TERMINAL, true, sh);
	}
	tcgetattr(sh->term_fd, &curr_term);
	return (curr_term);
}
