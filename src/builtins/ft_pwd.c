/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:31:30 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/25 18:15:09 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmd, t_shell sh)
{
	char	*cwd;

	(void) sh;
	cwd = NULL;
	cwd = xmc(getcwd(cwd, 0), NULL, 0, sh);
	write(cmd->out.fd, cwd, ft_strlen(cwd));
	write(cmd->out.fd, "\n", 1);
	free(cwd);
	return (0);
}
