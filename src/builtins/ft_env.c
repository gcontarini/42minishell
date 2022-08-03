/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:06:59 by nprimo            #+#    #+#             */
/*   Updated: 2022/08/03 20:48:05 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmd, t_shell *sh)
{
	t_dict	*var;
	t_list	*env;

	if (get_ac(cmd->av) > 1)
		return (ms_exit(127, ERRMSG_NOPERMISSION, false, sh));
	env = sh->env;
	while (env)
	{
		var = (t_dict *) env->content;
		if (var->value)
		{
			ft_putstr_fd(var->key, cmd->out.fd);
			ft_putstr_fd("=", cmd->out.fd);
			ft_putstr_fd(var->value, cmd->out.fd);
			ft_putstr_fd("\n", cmd->out.fd);
		}
		env = env->next;
	}
	return (0);
}
