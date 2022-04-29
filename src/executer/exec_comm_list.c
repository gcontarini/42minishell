/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_comm_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:19:09 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/28 17:45:47 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_comm_list(t_cmd *comm_list)
{
	int pos;

	pos = 0;
	while (comm_list[pos].av)
	{
		if (!comm_list->in.fname)
			comm_list->in.fd = 1;
		// else 
		// {
		// 	comm_list->in.fd = open(comm_list->in.fname, O_RDONLY);
		// 	...
		// }
		if (!comm_list->out.fname)
			comm_list->out.fd = 2;
		// same as for input
		if (exec_command(comm_list->in.fd, comm_list->out.fd, comm_list->av, NULL))
			return (1);
		pos++;
	}
	return (0);
}