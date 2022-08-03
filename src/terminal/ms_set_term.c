/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_term.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:53:40 by gcontari          #+#    #+#             */
/*   Updated: 2022/08/03 20:07:38 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_set_term(t_shell *sh)
{
	if (isatty(sh->term_fd) == 0
		|| tcsetattr(sh->term_fd, TCSANOW, &sh->new_term) < 0)
		ms_exit(1, ERRMSG_TERMINAL, true, sh);
	return ;
}
