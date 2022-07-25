/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:29:09 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/25 14:26:56 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int sig);

void	set_signals(void (*opt)(int), t_shell *sh)
{
	if (!opt)
		opt = sig_handler;
	if (signal(SIGINT, opt) == SIG_ERR
		|| signal(SIGQUIT, opt) == SIG_ERR)
	{
		free_shell(*sh);
		exit(0); // Which error?
	}
	return ;
}

static void	sig_handler(int sig)
{
	if (sig == SIGQUIT)
		return ;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}
