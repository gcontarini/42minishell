/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:24:04 by nprimo            #+#    #+#             */
/*   Updated: 2022/08/04 18:40:47 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_input(t_shell *sh);

int	shell_interactive(t_shell *sh)
{
	ms_set_term(sh);
	while (1)
	{
		set_signals(NULL, sh);
		sh->input = readline(PROMPT);
		if (!sh->input)
		{
			ms_restore_term(sh);
			free_shell(sh);
			ms_exit(0, "exit\n", true, sh);
		}
		else if (ft_strlen(sh->input) > 0)
		{
			add_history(sh->input);
			set_signals(SIG_IGN, sh);
			exec_input(sh);
		}
		else
		{
			sh->exit_status = 0;
			free(sh->input);
		}
	}
	return (0);
}

int	shell_from_file(int ac, char **av, t_shell *sh)
{
	int	fd;

	if (ac > 1)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			ms_exit(1, ERRMSG_OPENFILE, true, sh);
		sh->input = get_next_line(fd);
		while (sh->input)
		{
			exec_input(sh);
			sh->input = get_next_line(fd);
		}
		if (close(fd) == -1)
			ms_exit(1, ERRMSG_OPENFILE, true, sh);
	}
	return (0);
}

static int	exec_input(t_shell *sh)
{
	sh->last_exit_status = sh->exit_status;
	sh->token_list = parser(sh, sh->input);
	sh->cmd_list = get_cmd_list(&sh->token_list, sh);
	if (sh->exit_status == 0)
	{
		sh->exit_status = open_fd(sh->cmd_list, sh);
		sh->exit_status = exec_cmd_list(sh);
	}
	ft_lstclear(&sh->cmd_list, free_cmd);
	sh->cmd_list = NULL;
	free(sh->input);
	sh->token_list = NULL;
	return (0);
}
