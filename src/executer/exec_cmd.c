/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:24:52 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/25 15:30:35 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect(int fd_in, int fd_out);
static int	is_builitin(char *str);
static int	exec_builtin(t_cmd *cmd, t_shell *sh);
static int	exec_bin(t_cmd *cmd, t_shell *sh);
//
char		*find_bin_path(const char *bin, t_list *env, t_shell sh);
void		close_cmd_fd(t_cmd *cmd);

int	exec_cmd(t_cmd *cmd, t_shell *sh)
{
	if (cmd->av[0])
	{
		if (is_builitin(cmd->av[0]) >= 0)
			return (exec_builtin(cmd, sh));
		else
			return (exec_bin(cmd, sh));
	}
	close_cmd_fd(cmd);
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

static int	exec_builtin(t_cmd *cmd, t_shell *sh)
{
	static t_builtins	*builtin_list[] = {
		ft_echo, ft_env, ft_export, ft_exit, ft_pwd, ft_unset, ft_cd
	};
	int					pos;
	int					return_status;

	return_status = 0;
	pos = is_builitin(cmd->av[0]);
	return_status = builtin_list[pos](cmd, *sh);
	close_cmd_fd(cmd);
	return (return_status);
}

static int	exec_bin(t_cmd *cmd, t_shell *sh)
{
	pid_t	pid;
	char	*bin_path;
	char	**envp;

	if (access(cmd->av[0], F_OK & X_OK) == 0)
		bin_path = xmc(ft_strndup(cmd->av[0],
					ft_strlen(cmd->av[0])), NULL, 0, *sh);
	else
		bin_path = find_bin_path(cmd->av[0], sh->env, *sh);
	pid = fork();
	if (pid == -1)
		exit(1); // ?
	if (pid == 0)
	{
		set_signals(SIG_DFL, sh);
		error_check(redirect(cmd->in.fd, cmd->out.fd), *sh);
		envp = dict_list_to_av(sh->env, *sh);
		if (execve(bin_path, cmd->av, envp) == -1)
			sh->exit_status = 1; // find value that makes return = 127
		free_split(envp);
		exit(sh->exit_status);
	}
	close_cmd_fd(cmd);
	if (bin_path)
		free(bin_path);
	return (0);
}
