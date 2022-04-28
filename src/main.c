/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:14:41 by gcontarini        #+#    #+#             */
/*   Updated: 2022/04/28 17:16:32 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    static t_shell  sh;
    t_comm_list     *comm_list;

    //sh = init_sh();
    //register_all_signals(); // Add functions to handle each signal
    while (true)
    {
        sh.inpt = readline(PROMPT);
        add_history(sh.inpt);
        ft_printf("INPUT: %s\n", sh.inpt);
        comm_list = get_comm_list(sh.inpt);
        exec_comm_list(comm_list);
        //exec_inpt(parse_input() => do_cmd()); // => wait for process???
        //free_input(); Check if we can free memory that is added to history
    }
    //free_and_exit(); // Exit gracefully
    return (0);
} 