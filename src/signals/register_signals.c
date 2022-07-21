/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:58:57 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/21 19:45:45 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_shell_pid;

static void	redo_prompt(void);
static void	sig_handler(int sig, siginfo_t *info, void *ucontext);

// Needs a here doc control to avoid not closing it when necessary
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

static void	redo_prompt(void)
{
	write(2, "\n", 1);
	rl_replace_line("", 0);
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
	if (sig == SIGINT) // SIGQUIT SHOULD DO NOTHING, RIGHT NOW IT SETS THE CURSOR POSITION TO START, INSTEAD TAKE THE CURSOR POSITION AND SET IT BACK TO THIS POSITION
		redo_prompt();
	(void) ucontext;
	return ;
}
