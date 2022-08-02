/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:24:52 by nprimo            #+#    #+#             */
/*   Updated: 2022/08/02 21:35:38 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect(int fd_in, int fd_out);
static int	exec_builtin(t_cmd *cmd, t_shell *sh);
static int	exec_bin(t_cmd *cmd, t_shell *sh);
static void	child_exec_bin(char *bpath, char **envp, t_cmd *cmd, t_shell *sh);

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

static int	exec_builtin(t_cmd *cmd, t_shell *sh)
{
	static t_builtins	*builtin_list[] = {
		ft_echo, ft_env, ft_export, ft_exit, ft_pwd, ft_unset, ft_cd
	};
	int					pos;
	int					return_status;
	pid_t				pid;

	return_status = 0;
	pid = fork();
	if (pid == -1)
		ms_exit(1, NULL, true, sh); // Which number and message?
	if (pid == 0)
	{
		pos = is_builitin(cmd->av[0]);
		return_status = builtin_list[pos](cmd, sh);
		close_cmd_fd(cmd);
		ms_exit(return_status, NULL, true, sh); // Which number and message?
	}
	close_cmd_fd(cmd);
	return (return_status);
}

static int	exec_bin(t_cmd *cmd, t_shell *sh)
{
	pid_t	pid;
	char	*bin_path;
	char	**envp;

	envp = NULL;
	if (access(cmd->av[0], F_OK & X_OK) == 0)
		bin_path = xmc(ft_strndup(cmd->av[0],
					ft_strlen(cmd->av[0])), NULL, 0, sh);
	else
		bin_path = find_bin_path(cmd->av[0], sh->env, sh);
	pid = fork();
	if (pid == -1)
		ms_exit(1, NULL, true, sh); // Which number and message?
	if (pid == 0)
		child_exec_bin(bin_path, envp, cmd, sh);
	close_cmd_fd(cmd);
	if (bin_path)
		free(bin_path);
	return (0);
}

static void	child_exec_bin(char *bpath, char **envp, t_cmd *cmd, t_shell *sh)
{
	set_signals(SIG_DFL, sh);
	error_check(redirect(cmd->in.fd, cmd->out.fd), sh);
	envp = dict_list_to_av(sh->env, sh);
	if (execve(bpath, cmd->av, envp) == -1)
		sh->exit_status = 127;
	free_split(envp);
	ms_exit(sh->exit_status, NULL, true, sh);
	return ;
}
