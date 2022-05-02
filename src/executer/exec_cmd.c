/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:24:52 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/02 12:18:55 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect(int fd_in, int fd_out);

// int	exec_cmd(int fd_in, int fd_out, char **av, char **envp)
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
		if (redirect(cmd.in.fd, cmd.out.fd) == -1)
			exit(1);
		if (execve(bin_path, cmd.av, envp) == -1)
			exit(1);
	}
	if (waitpid(pid, NULL, 0) == -1)
		exit(1);
	if (close(cmd.in.fd) == -1 || close(cmd.out.fd))
		exit(1);
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
