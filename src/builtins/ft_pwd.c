/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:31:30 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/31 16:02:01 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmd, t_shell *sh)
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
