/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:18:18 by gcontari          #+#    #+#             */
/*   Updated: 2022/06/18 15:06:32 by nprimo           ###   ########.fr       */
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
typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;
typedef unsigned long	t_ulong;

// VARIABLES

typedef struct s_fd
{
	char	*fname;
	char	*redirection;
	int		fd;
}	t_fd;

typedef struct s_cmd
{
	t_list	*token_list;
	char	**av;
	//char	**envp;
	t_fd	in;
	t_fd	out;
	// Maybe more stuff for redirects etc etc
}	t_cmd;

typedef struct s_dict {
    char    *key;
    char    *value;
}   t_dict;

typedef struct s_shell
{
	t_list	*env;
	char	*input;
	t_list	*token_list;
	t_list	*cmd_list;
}	t_shell;

// FUNCTIONS
// core
void	free_split(char **av);
void	free_cmd(void	*cmd_void);
void	free_dict(void *var_void);
//
t_shell init_shell(char **envp);
//
void	print_cmd_list(t_list *cmd_list);
void	print_llist(t_list *llist);
//
char	**llist_to_av(t_list *llist);
int		is_in_set(char *str, char **str_set);

// error handling
void	*error_check_pointer(void *pointer);
void	error_check(int ret_value);

// parser
int		get_token_list(const char *input, t_list **token_list);
t_list	*get_cmd_list(t_list *token_list);

// executer
char	*find_bin_path(const char *cmd);
int		exec_cmd(t_cmd cmd, char **envp);
int		exec_cmd_list(t_list *comm_list);
int 	open_fd(t_list *cmd_list);

// builtins
int		ft_echo(t_cmd *cmd);

#endif