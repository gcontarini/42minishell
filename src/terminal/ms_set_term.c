/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_term.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:53:40 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/31 16:13:58 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_set_term(t_shell *sh)
{
	if (isatty(sh->term_fd) == 0
		|| tcsetattr(sh->term_fd, TCSANOW, &sh->new_term) < 0)
	{
		free_shell(sh);
		exit(INVALID_TERM);
	}
	return ;
}
