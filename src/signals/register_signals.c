/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:29:09 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/24 16:20:28 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int sig, siginfo_t *info, void *ucontext);

void	set_signals(int opt, t_shell *sh)
{
	struct sigaction	sa;

	if (opt != 0)
	{
		if (signal(SIGINT, opt) == SIG_ERR
			|| signal(SIGQUIT, opt) == SIG_ERR)
		{
			free_shell(*sh);
			exit(0); // Which error?
		}
		return ;
	}
	ft_memset(&sa, '\0', sizeof(sa));
	sigemptyset(&(sa.sa_mask));
	sigaddset(&(sa.sa_mask), SIGINT);
	sigaddset(&(sa.sa_mask), SIGQUIT);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1
		|| sigaction(SIGQUIT, &sa, NULL == -1))
	{
		free_shell(*sh);
		exit(0);
	}
}

static void	sig_handler(int sig, siginfo_t *info, void *ucontext)
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
	(void) info;
	(void) ucontext;
	return ;
}
