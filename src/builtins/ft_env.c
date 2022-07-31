/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:06:59 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/31 16:04:42 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmd, t_shell *sh)
{
	t_dict	*var;
	t_list	*env;

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
