/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_config_termios.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:45:51 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/21 19:40:27 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_term	ms_config_termios(t_shell *sh)
{
	t_term	new_term;

	new_term = sh->old_term;
	new_term.c_lflag &= ~ECHOCTL;
	return (new_term);
}
