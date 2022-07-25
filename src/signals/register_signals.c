/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:29:09 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/25 18:15:25 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int sig);
static void	sig_exit_here_doc(int sig);

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

void	set_here_doc_signal(t_shell *sh)
{
	set_signals(SIG_DFL, NULL);
	if (signal(SIGINT, sig_exit_here_doc) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		free_shell(*sh);
		exit(0); // ERRO no?
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

static void	sig_exit_here_doc(int sig)
{
	(void) sig;
	exit(42); // Check this shit
	return ;
}
