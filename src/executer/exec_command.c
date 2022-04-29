/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:24:52 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/29 14:42:32 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect(int fd_in, int fd_out);

int	exec_command(int fd_in, int fd_out, char **av, char **envp)
{
	pid_t	pid;
	char	*bin_path;

	bin_path = find_bin_path(av[0]);
	if (!bin_path || ft_strlen(bin_path) == 0)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		if (redirect(fd_in, fd_out) == -1)
			exit(1);
		if (execve(bin_path, av, envp) == -1)
			exit(1);
	}
	if (waitpid(pid, NULL, 0) == -1)
		exit(1);
	if (close(fd_in) == -1 || close(fd_out))
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
