/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:24:52 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/28 16:18:46 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_command(int fd_in, int fd_out, char **av, char **envp)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid == -1)
		exit(1);
	cmd_path = find_cmd_path(av[0], envp);
	if (!cmd_path)
		exit(1);
	if (pid == 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1
			|| dup2(fd_out, STDOUT_FILENO) == -1)
			exit(1);
		if (close(fd_in) == -1 || close(fd_out) == -1)
			exit(1);
		if (execve(cmd_path, av, envp) == -1)
			exit(1);
	}
	if (waitpid(pid, NULL, 0) == -1)
		exit(1);
	if (close(fd_in) == -1 || close(fd_out))
		exit(1);
	free(cmd_path);
	return (0);
}

// int	main(void)
// 
// 	int		fd_in;
// 	int		fd_out;
// 	int		fd_pipe[2];
// 	char	*av0[] = {PATH_CAT, NULL};
// 	char	*av1[] = {PATH_WC, NULL};

// 	fd_in = open("file1", O_RDONLY);
// 	fd_out = open("file2", O_WRONLY);
// 	if (fd_in == -1 || fd_out == -1)
// 		exit(1); //verbose
// 	if (pipe(fd_pipe) == -1)
// 		exit(1);
// 	exec_command(fd_in, fd_pipe[1], av0);
// 	exec_command(fd_pipe[0], fd_out, av1);
// 	close(fd_in);
// 	close(fd_out);
// 	return (0);
// }
