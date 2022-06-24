/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:18:18 by gcontari          #+#    #+#             */
/*   Updated: 2022/06/24 21:15:41 by nprimo           ###   ########.fr       */
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
# include "get_next_line.h"

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
}				t_fd;

typedef struct s_cmd
{
	t_list	*token_list;
	char	**av;
	t_fd	in;
	t_fd	out;
}				t_cmd;

typedef struct s_dict
{
	char	*key;
	char	*value;
}				t_dict;

typedef struct s_shell
{
	t_list	*env;
	char	*input;
	t_list	*token_list;
	t_list	*cmd_list;
}				t_shell;

typedef enum e_struct_type
{
	T_SPLIT,
	T_CMD,
	T_DICT,
	T_FD
}				t_struct_type;

typedef void			(*t_free_func) (void *);
typedef int				(t_builtins) (t_cmd *, t_shell);

// FUNCTIONS
// core
void	free_split(void *av_void);
void	free_cmd(void *cmd_void);
void	free_dict(void *var_void);
void	free_fd(void *fd_void);
void	free_shell(t_shell sh);
//
t_shell	init_shell(char **envp);
int		shell_interactive(t_shell sh);
int		shell_from_file(int ac, char **av, t_shell sh);

//
void	print_cmd_list(t_list *cmd_list);
void	print_llist(t_list *llist);
//
char	**llist_to_av(t_list *llist);
char	**dict_list_to_av(t_list *dict_list);
t_dict	*str_to_dict(char *str);

//
int		is_in_set(char *str, char **str_set);
//
char	*ft_getenv(const char *name, t_list *env);
t_dict	*get_dict_var(const char *key, t_list *dict);

// error handling
void	*error_check_pointer(void *pointer);
void	error_check(int ret_value);

// parser
int		get_token_list(const char *input, t_list **token_list);
t_list	*get_cmd_list(t_list *token_list);

// executer
char	*find_bin_path(const char *cmd, t_list *env);
int		exec_cmd(t_cmd *cmd, t_shell sh);
int		exec_cmd_list(t_shell sh);
int		open_fd(t_list *cmd_list);

// builtins
int		ft_echo(t_cmd *cmd, t_shell sh);
int		ft_env(t_cmd *cmd, t_shell sh);
int		ft_export(t_cmd *cmd, t_shell sh);
int		ft_exit(t_cmd *cmd, t_shell sh);
int		ft_pwd(t_cmd *cmd, t_shell sh);
int		ft_unset(t_cmd *cmd, t_shell sh);

#endif