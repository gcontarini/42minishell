/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:24:52 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/05 16:00:48 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect(int fd_in, int fd_out);

int	exec_cmd(t_cmd cmd, char **envp)
{
	pid_t	pid;
	char	*bin_path;

	bin_path = find_bin_path(cmd.av[0]);
	if (!bin_path || ft_strlen(bin_path) == 0)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		error_check(redirect(cmd.in.fd, cmd.out.fd));
		error_check(execve(bin_path, cmd.av, envp));
	}
	error_check(waitpid(pid, NULL, 0));
	error_check(close(cmd.in.fd));
	error_check(close(cmd.out.fd));
	free(bin_path);
	return (0);
}

static int	redirect(int fd_in, int fd_out)
{
	if (fd_in != 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1
			|| close(fd_in) == -1)
			return (-1);
	}
	if (fd_out != 1)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1
			|| close(fd_out) == -1)
			return (-1);
	}
	return (0);
}
