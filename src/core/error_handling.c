/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:31:54 by nprimo            #+#    #+#             */
/*   Updated: 2022/08/02 09:17:41 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*xmc(void *ptr, void *var, t_struct_type type, t_shell *sh)
{
	static t_free_func	free_func_list[] = {
		free_split, free_cmd, free_dict, free_fd, free_exp, free_token, free
	};

	if (!ptr)
	{
		if (var)
			free_func_list[type](var);
		free_shell(sh);
		ms_exit(1, ERRMSG_MEM_FAIL, true, sh); // which number
	}
	return (ptr);
}

void	error_check(int ret_value, t_shell *sh)
{
	if (ret_value < 0)
	{
		printf("User perror to print specific things...\n");
		free_shell(sh);
		ms_exit(1, ERRMSG_GENERIC, true, sh); // which number
	}
}

int	ofile_checker(int fd, t_shell *sh)
{
	if (fd < 0)
	{
		ms_exit(42, "\n", false, sh); // which number and message
		return (1);
	}
	return (0);
}
