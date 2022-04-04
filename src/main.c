#include "minishell.h"

int main(void)
{
    static t_shell  sh;

    sh = init_sh();
    //register_all_signals(); // Add functions to handle each signal
    while (true)
    {
        inpt = readline(PROMPT);
        //create_history();
        exec_inpt(parse_input() => do_cmd()); // => wait for process???
        //free_input(); Check if we can free memory that is added to history
    }
    //free_and_exit(); // Exit gracefully
    return (0);
}

// Implement basic parser
// Do a pipex
// Create working history
//  * Save last exit code somehow
// Implement basic parsing without pipes and redirections (parser)
//  * Parser will return a struct with the correct order of cmds, and with flags
// Implement bullits
//  * cd
//  * echo
//  * pwd
//  * exit
//  * env       | 
//  * export    | All handles env variable
//  * unset     |
// Signal handling for
//  * C
//  * D
//  * \