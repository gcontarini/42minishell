/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:24:04 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/20 19:25:50 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_input(t_shell sh);

int	shell_interactive(t_shell sh)
{
	while (1)
	{
		sh.input = readline(PROMPT);
		add_history(sh.input);
		exec_input(sh);
	}
	return (0);
}

int	shell_from_file(int ac, char **av, t_shell sh)
{
	int	fd;

	if (ac > 1)
	{
		fd = open(av[1], O_RDONLY);
		error_check(fd);
		sh.input = get_next_line(fd);
		while (sh.input)
		{
			exec_input(sh);
			sh.input = get_next_line(fd);
		}
		error_check(close(fd));
	}
	return (0);
}

static int	exec_input(t_shell sh)
{
	error_check(get_token_list(sh.input, &sh.token_list));
	sh.cmd_list = get_cmd_list(sh.token_list);
	open_fd(sh.cmd_list);
	exec_cmd_list(sh);
	ft_lstclear(&sh.cmd_list, free_cmd);
	sh.cmd_list = NULL;
	free(sh.input);
	sh.token_list = NULL;
	return (0);
}
