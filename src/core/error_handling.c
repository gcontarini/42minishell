/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:31:54 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/01 20:02:03 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*xmc(void *ptr, void *var, t_struct_type type, t_shell sh)
{
	static t_free_func	free_func_list[] = {
		free_split, free_cmd, free_dict, free_fd, free_exp, free_token, free
	};

	if (!ptr)
	{
		printf("Memory allocation failed!\n");
		if (var)
			free_func_list[type](var);
		free_shell(sh);
		exit(1);
	}
	return (ptr);
}

void	error_check(int ret_value, t_shell sh)
{
	if (ret_value < 0)
	{
		printf("User perror to print specific things...\n");
		free_shell(sh);
		exit(1);
	}
}
