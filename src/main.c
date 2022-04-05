#include "minishell.h"

int main(void)
{
    static t_shell  sh;

    //sh = init_sh();
    //register_all_signals(); // Add functions to handle each signal
    while (true)
    {
        sh.inpt = readline(PROMPT);
        ft_printf("%s\n", sh.inpt);
        //create_history();
        //exec_inpt(parse_input() => do_cmd()); // => wait for process???
        //free_input(); Check if we can free memory that is added to history
    }
    //free_and_exit(); // Exit gracefully
    return (0);
}