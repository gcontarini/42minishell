/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:31:54 by nprimo            #+#    #+#             */
/*   Updated: 2022/08/03 20:16:46 by nprimo           ###   ########.fr       */
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
		ms_exit(1, ERRMSG_MEM_FAIL, true, sh);
	}
	return (ptr);
}

int	ofile_checker(int fd, t_shell *sh)
{
	if (fd < 0)
		return (ms_exit(1, ERRMSG_OPENFILE, false, sh));
	return (0);
}
