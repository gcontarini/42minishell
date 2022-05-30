/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:18:18 by gcontari          #+#    #+#             */
/*   Updated: 2022/05/30 17:05:58 by nprimo           ###   ########.fr       */
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

// MACROS
# define PROMPT "minishell0.0$ " 
# define METACHAR_SET "|&<>" // ;()
# define SPACE_SET " \n\t"

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

typedef struct s_fd
{
	char	*fname;
	int		fd;
}	t_fd;

typedef struct  s_cmd
{
	t_list	*token_list;
	char	**av;
	//char	**envp;
	t_fd	in;
	t_fd	out;
    // Maybe more stuff for redirects etc etc
}   t_cmd;

// FUNCTIONS
// core
void	free_split(char **av);
void	free_cmd(void *void_cmd);
void	print_cmd_list(t_list *cmd_list);
void 	print_llist(t_list *llist);
char	**llist_to_av(t_list *llist);

// error handling
void	*error_check_pointer(void *pointer);
void	error_check(int	ret_value);

// parser
int		get_token_list(const char *input, t_list **token_list);
t_list	*get_cmd_list(t_list *token_list);
int		is_control_operator(void *void_token);

// execture
char	*find_bin_path(const char *cmd);
int		exec_cmd(t_cmd cmd, char **envp);
int 	exec_cmd_list(t_list *comm_list);

// builtins
int		ft_echo(t_cmd *cmd);

#endif