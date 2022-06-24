/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:24:52 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/24 21:15:55 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builitin(char *str);
static int	redirect(int fd_in, int fd_out);
static int	exec_bin(t_cmd *cmd, t_shell sh);
static int	exec_builtin(t_cmd *cmd, t_shell sh);

int	exec_cmd(t_cmd *cmd, t_shell sh)
{
	if (is_builitin(cmd->av[0]))
		return (exec_builtin(cmd, sh));
	else
		return (exec_bin(cmd, sh));
}

static int	is_builitin(char *str)
{
	static char	*builtin_list[] = {
		"echo", "env", "export", "exit", "pwd", "unset", NULL};
	int			pos;

	pos = 0;
	while (builtin_list[pos])
	{
		if (ft_strncmp(builtin_list[pos], str,
				ft_strlen(builtin_list[pos]) + 1) == 0)
			return (1);
		pos++;
	}
	return (0);
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

static int	exec_bin(t_cmd *cmd, t_shell sh)
{
	pid_t	pid;
	char	*bin_path;

	bin_path = find_bin_path(cmd->av[0], sh.env);
	if (!bin_path)
		exit(1);
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

int	exec_builtin(t_cmd *cmd, t_shell sh)
{
	int	return_status;

	return_status = 0;
	if (ft_strncmp("echo", cmd->av[0], ft_strlen("echo") + 1) == 0)
		return_status = ft_echo(cmd, sh);
	else if (ft_strncmp("env", cmd->av[0], ft_strlen("env") + 1) == 0)
		return_status = ft_env(cmd, sh);
	else if (ft_strncmp("export", cmd->av[0], ft_strlen("export") + 1) == 0)
		return_status = ft_export(cmd, sh);
	else if (ft_strncmp("exit", cmd->av[0], ft_strlen("exit") + 1) == 0)
		return_status = ft_exit(cmd, sh);
	else if (ft_strncmp("pwd", cmd->av[0], ft_strlen("pwd") + 1) == 0)
		return_status = ft_pwd(cmd, sh);
	else if (ft_strncmp("unset", cmd->av[0], ft_strlen("unset") + 1) == 0)
		return_status = ft_unset(cmd, sh);
	if (cmd->in.fd != STDIN_FILENO)
		close(cmd->in.fd);
	if (cmd->out.fd != STDOUT_FILENO)
		close(cmd->out.fd);
	return (0);
}
