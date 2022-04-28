/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:23:46 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/28 17:41:03 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

char	*find_cmd_path(const char *cmd);
int		exec_command(int fd_in, int fd_out, char **av, char **envp);
void	free_split(char **av);
int 	exec_comm_list(t_cmd *comm_list);

#endif