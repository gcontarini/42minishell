/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:36:50 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/04 13:18:25 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *eof)
{
	int		fd_pipe[2];
	char	*new_line;

	if (pipe(fd_pipe) == -1)
		return (-1);
	new_line = readline("> ");
	while (ft_strncmp(new_line, eof, ft_strlen(eof) + 1))
	{
		ft_putstr_fd(new_line, fd_pipe[1]);
		free(new_line);
		ft_putstr_fd("\n", fd_pipe[1]);
		new_line = readline("> ");
	}
	close(fd_pipe[1]);
	free(new_line);
	return (fd_pipe[0]);
}
