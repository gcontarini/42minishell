/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:36:50 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/25 19:06:02 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_close_pipe(int pipe[2], int status);
static void	child_here_doc(char *eof, int fd_pipe[2]);

int	here_doc(char *eof, t_shell *sh)
{
	int		fd_pipe[2];
	int		status;
	pid_t	pid;

	if (pipe(fd_pipe) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (_close_pipe(fd_pipe, -1)); // error no?
	if (pid == 0)
	{
		set_here_doc_signal(sh);
		child_here_doc(eof, fd_pipe);
		exit(0);
		return (0);
	}
	waitpid(0, &status, 0);
	printf("STATUS: %d\n", status);
	if (status != 0)
		return (_close_pipe(fd_pipe, -1)); // error no?
	return (fd_pipe[0]);
}

static void	child_here_doc(char *eof, int fd_pipe[2])
{
	char	*new_line;

	new_line = readline("> ");
	while (new_line && ft_strncmp(new_line, eof, ft_strlen(eof) + 1))
	{
		ft_putstr_fd(new_line, fd_pipe[1]);
		free(new_line);
		ft_putstr_fd("\n", fd_pipe[1]);
		new_line = readline("> ");
	}
	close(fd_pipe[1]);
	free(new_line);
	return ;
}

static int	_close_pipe(int pipe[2], int status)
{
	close(pipe[0]);
	close(pipe[1]);
	return (status);
}
