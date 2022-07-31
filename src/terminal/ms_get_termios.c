/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_termios.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:44:23 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/31 16:13:43 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_term	ms_get_termios(t_shell *sh)
{
	t_term	curr_term;

	if (isatty(sh->term_fd) == 0)
	{
		free_shell(sh);
		exit(INVALID_TERM);
	}
	tcgetattr(sh->term_fd, &curr_term);
	return (curr_term);
}
