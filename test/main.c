/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:54:57 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/17 19:50:54 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	static t_shell	sh;

	sh = init_sell(envp);
	while (1)
	{
		sh.input = readline(PROMPT);
		add_history(sh.input);
		sh->token_list = parser(sh, sh->input);
		sh->cmd_list = get_cmd_list(&sh->token_list, sh);
			if (sh->exit_status == 0)
	}
}
