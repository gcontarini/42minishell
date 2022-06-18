/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:14:41 by gcontarini        #+#    #+#             */
/*   Updated: 2022/06/18 17:58:08 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	static t_shell	sh;

	sh = init_shell(envp);
	if (ac == 1)
	{
		while (1)
		{
			sh.input = readline(PROMPT);
			add_history(sh.input);
			error_check(get_token_list(sh.input, &sh.token_list));
			free(sh.input);
			sh.cmd_list = get_cmd_list(sh.token_list);
			open_fd(sh.cmd_list);
			exec_cmd_list(sh);
			ft_lstclear(&sh.cmd_list, free_cmd);
			sh.token_list = NULL;
		}
	}
	else
		printf("do something with %s", av[1]);
	return (0);
}
