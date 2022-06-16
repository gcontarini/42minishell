/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:14:41 by gcontarini        #+#    #+#             */
/*   Updated: 2022/06/16 15:38:56 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    static t_shell  sh;
    t_list          *cmd_list;
    t_list          *token_list;

    //sh = init_sh();
    //register_all_signals(); // Add functions to handle each signal
    // find a way to loop: while loop cause segfault
    while (1)
    {
        sh.inpt = readline(PROMPT);
        add_history(sh.inpt);
        token_list = NULL;
        error_check(get_token_list(sh.inpt, &token_list));
        free(sh.inpt);
        cmd_list = get_cmd_list(token_list);
        open_fd(cmd_list);
        exec_cmd_list(cmd_list);
        ft_lstclear(&cmd_list, free_cmd);
    }
    return (0);
} 