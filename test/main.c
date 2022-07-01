/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:54:57 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/01 16:41:28 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test(t_shell sh)
{
	printf("T: %p\n", &sh.token_list);
}

int	main(int ac, char **argv, char **envp)
{
	char	*str = "echoas'dfasd'asdfsad";
	char	*av[] = { "/usr/bin/echo", str, NULL };

	execve("/usr/bin/echo", av, NULL);
}

// int here_doc(char *eof, t_shell sh)
// {
// 	int		fd_pipe[2];
// 	char	*new_line;
// 	char	*tmp;

// 	if (pipe(fd_pipe) == -1)
// 		return (-1);
// 	new_line = readline("> ");
// 	while (ft_strncmp(new_line, eof, ft_strlen(eof) + 1))
// 	{
// 		ft_putstr_fd(new_line, fd_pipe[1]);
// 		free(new_line);
// 		ft_putstr_fd("\n", fd_pipe[1]);
// 		new_line = readline("> ");
// 	}
// 	free(new_line);
// 	return (fd_pipe[0]);
// }
