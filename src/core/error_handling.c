/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:31:54 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/05 16:02:11 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*error_check_pointer(void *pointer)
{
	if (!pointer)
	{
		printf("User perror to print specific things...\n");
		// free all
		exit(1); // exit with errno
	}
	return (pointer);
}

void	error_check(int	ret_value)
{
	if (ret_value < 0)
	{
		printf("User perror to print specific things...\n");
		// free all
		exit(1); // exit with errno
	}
}
