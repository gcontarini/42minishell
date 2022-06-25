/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:24:52 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/25 17:10:18 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect(int fd_in, int fd_out);
static int	is_builitin(char *str);
static int	exec_builtin(t_cmd *cmd, t_shell sh);
static int	exec_bin(t_cmd *cmd, t_shell sh);
//
char		*find_bin_path(const char *bin, t_list *env, t_shell sh);

int	exec_cmd(t_cmd *cmd, t_shell sh)
{
	if (is_builitin(cmd->av[0]) >= 0)
		return (exec_builtin(cmd, sh));
	else
		return (exec_bin(cmd, sh));
}

static int	redirect(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1
			|| close(fd_in) == -1)
			return (-1);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1
			|| close(fd_out) == -1)
			return (-1);
	}
	return (0);
}

static int	is_builitin(char *str)
{
	static char	*builtin_list[] = {
		"echo", "env", "export", "exit", "pwd", "unset", "cd", NULL};
	int			pos;

	pos = 0;
	while (builtin_list[pos])
	{
		if (ft_strncmp(builtin_list[pos], str,
				ft_strlen(builtin_list[pos]) + 1) == 0)
			return (pos);
		pos++;
	}
	return (-1);
}

int	exec_builtin(t_cmd *cmd, t_shell sh)
{
	static t_builtins	*builtin_list[] = {
		ft_echo, ft_env, ft_export, ft_exit, ft_pwd, ft_unset, ft_cd
	};
	int					pos;
	int					return_status;

	return_status = 0;
	pos = is_builitin(cmd->av[0]);
	return_status = builtin_list[pos](cmd, sh);
	if (cmd->in.fd != STDIN_FILENO)
		close(cmd->in.fd);
	if (cmd->out.fd != STDOUT_FILENO)
		close(cmd->out.fd);
	return (0);
}

static int	exec_bin(t_cmd *cmd, t_shell sh)
{
	pid_t	pid;
	char	*bin_path;

	bin_path = find_bin_path(cmd->av[0], sh.env, sh);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		error_check(redirect(cmd->in.fd, cmd->out.fd));
		error_check(execve(bin_path, cmd->av, dict_list_to_av(sh.env)));
	}
	if (cmd->in.fd != STDIN_FILENO)
		close(cmd->in.fd);
	if (cmd->out.fd != STDOUT_FILENO)
		close(cmd->out.fd);
	free(bin_path);
	return (0);
}
