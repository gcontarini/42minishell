/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:29:09 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/22 17:29:16 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_shell_pid;

static void	redo_prompt(int sig);
static void	sig_handler(int sig, siginfo_t *info, void *ucontext);

void	register_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&(sa.sa_mask));
	sigaddset(&(sa.sa_mask), SIGINT);
	sigaddset(&(sa.sa_mask), SIGQUIT);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	kill(0, SIGINT);
}

static void	redo_prompt(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
	}
	else if (sig == SIGQUIT)
		write(STDERR_FILENO, "", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

static void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	if (g_shell_pid == 0)
	{
		g_shell_pid = info->si_pid;
		return ;
	}
	if (g_shell_pid != info->si_pid)
		return ;
	redo_prompt(sig);
	(void) ucontext;
	return ;
}
