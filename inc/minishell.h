/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:18:18 by gcontari          #+#    #+#             */
/*   Updated: 2022/04/28 15:25:31 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include "parser.h"

// MACROS
#define PROMPT "minishell0.0$ " 

// ALIAS
typedef unsigned int    t_uint; 
typedef unsigned char   t_uchar; 
typedef unsigned long   t_ulong; 

// VARIABLES
typedef struct  s_shell
{
    char    *inpt;
    char    **parsed;
//    t_llst *pids(t_ulong);
}   t_shell;

typedef struct  s_cmd
{
    char    *bin;
    char    *args;
    // Maybe more stuff for redirects etc etc
}   t_cmd;

// FUNCTIONS

#endif