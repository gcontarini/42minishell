/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:18:18 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/25 17:58:46 by gcontari         ###   ########.fr       */
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
# include <termios.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

// MACROS
# define PROMPT "minishell0.0$ " 
# define METACHAR_SET "|&<>" // ;()
# define SPACE_SET " \n\t"
# define EXP_SET "|&<> \n\t\'\""
# define INVALID_TERM 0 // Don't know what to use

// ALIAS
typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;
typedef unsigned long	t_ulong;
typedef struct termios	t_term;

typedef enum e_struct_type
{
	T_SPLIT,
	T_CMD,
	T_DICT,
	T_FD,
	T_EXP,
	T_TOKEN,
	T_MEM
}	t_struct_type;

typedef enum e_token_type
{
	CON_TOKEN,
	I_TOKEN,
	CON_QUOTE,
	I_QUOTE,
	CON_REDIR,
	I_REDIR
}	t_ttype;

// VARIABLES
typedef struct s_fd
{
	char	*fname;
	char	*redirection;
	int		fd;
}	t_fd;

typedef struct s_cmd
{
	char	**av;
	t_fd	in;
	t_fd	out;
}	t_cmd;

typedef struct s_dict
{
	char	*key;
	char	*value;
}	t_dict;

typedef struct s_shell
{
	t_list			*env;
	char			*input;
	char			*homepath;
	t_list			*token_list;
	t_list			*cmd_list;
	int				exit_status;
	int				term_fd;
	struct termios	old_term;
	struct termios	new_term;
}	t_shell;

typedef struct s_expander
{
	t_uint	counter;
	char	**var_names;
	bool	*table;
}	t_exp;

typedef struct s_token
{
	char	*s;
	t_ttype	t;
}	t_token;

typedef void			(*t_free_func) (void *);
typedef int				(t_builtins) (t_cmd *, t_shell);

// FUNCTIONS
// builtins
int		ft_echo(t_cmd *cmd, t_shell sh);
int		ft_env(t_cmd *cmd, t_shell sh);
int		ft_export(t_cmd *cmd, t_shell sh);
int		ft_exit(t_cmd *cmd, t_shell sh);
int		ft_pwd(t_cmd *cmd, t_shell sh);
int		ft_unset(t_cmd *cmd, t_shell sh);
int		ft_cd(t_cmd *cmd, t_shell sh);

// core
void	free_split(void *av_void);
void	free_cmd(void *cmd_void);
void	free_dict(void *var_void);
void	free_fd(void *fd_void);
void	free_exp(void *exp_void);
void	free_token(void *token_void);
void	free_t(void *token_void);

void	free_shell(t_shell sh);
// shell
t_shell	init_shell(char **envp);
int		shell_interactive(t_shell sh);
int		shell_from_file(int ac, char **av, t_shell sh);

//
void	print_cmd_list(t_list *cmd_list);
void	print_llist(t_list *llist);
//
char	**llist_to_av(t_list *llist, t_shell sh);
char	**dict_list_to_av(t_list *dict_list, t_shell sh);
t_dict	*str_to_dict(char *str, t_shell sh);

//
int		is_in_set(char *str, char **str_set);
//
char	*ft_getenv(const char *name, t_list *env);
t_dict	*get_dict_var(const char *key, t_list *dict);

// error handling
void	*xmc(void *ptr, void *var, t_struct_type type, t_shell sh);
void	*error_check_pointer(void *pointer);
void	error_check(int ret_value, t_shell sh);
int		ofile_checker(int fd, t_shell *sh);

// executer
int		exec_cmd(t_cmd *cmd, t_shell *sh);
int		exec_cmd_list(t_shell *sh);
int		open_fd(t_list *cmd_list, t_shell sh);
int		here_doc(char *eof);

// parser
t_list	*parser(t_shell *sh, const char *inpt);
t_uint	str_count_char(const char *s, char c);
t_list	*get_cmd_list(t_list **token_list, t_shell *s_shell);
t_list	*lexer(t_shell sh, const char *inpt);
char	*expander(t_shell sh, const char *input);
t_list	*build_syntax_tree(t_shell *sh);

// signals
void	set_signals(void (*opt)(int), t_shell *sh);

// terminal
t_term	ms_config_termios(t_shell *sh);
t_term	ms_get_termios(t_shell *sh);
void	ms_restore_term(t_shell *sh);
void	ms_set_term(t_shell *sh);

#endif