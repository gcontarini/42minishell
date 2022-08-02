/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_restore_term.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:53:40 by gcontari          #+#    #+#             */
/*   Updated: 2022/08/02 09:04:44 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_restore_term(t_shell *sh)
{
	if (isatty(sh->term_fd) == 0
		|| tcsetattr(sh->term_fd, TCSANOW, &sh->old_term) < 0)
	{
		free_shell(sh);
		ms_exit(INVALID_TERM, ERRMSG_TERMINAL, true, sh);
	}
	return ;
}
