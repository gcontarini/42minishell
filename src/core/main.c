/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:14:41 by gcontarini        #+#    #+#             */
/*   Updated: 2022/05/02 12:13:48 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    static t_shell  sh;
    t_list           *cmd_list;

    //sh = init_sh();
    //register_all_signals(); // Add functions to handle each signal
    // find a way to loop: while loop cause segfault
    sh.inpt = readline(PROMPT);
    add_history(sh.inpt);
    ft_printf("INPUT: %s\n", sh.inpt);
    cmd_list = get_cmd_list(sh.inpt);
    // print_cmd_list(cmd_list);
    if (exec_cmd_list(cmd_list) == 1)
        return (1) ;
    //exec_inpt(parse_input() => do_cmd()); // => wait for process???
    //free_input(); Check if we can free memory that is added to history
    //free_and_exit(); // Exit gracefully
    free(sh.inpt);
    return (0);
} 