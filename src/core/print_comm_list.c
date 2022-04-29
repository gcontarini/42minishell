/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_comm_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:10:51 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/29 12:13:36 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_av(char **av);

void	print_comm_list(t_cmd *comm_list)
{
	int pos;

	pos = 0;
	while (comm_list && comm_list[pos].av)
	{
		print_av(comm_list[pos].av);
		pos++;
	}
}

static void	print_av(char **av)
{
	int pos;

	pos = 0;
	while (av && av[pos])
	{
		printf("%s\n", av[pos]);
		pos++;
	}
}