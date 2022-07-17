/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:06:59 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/17 20:20:15 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmd, t_shell sh)
{
	t_dict	*var;
	t_list	*env;

	env = sh.env;
	while (env)
	{
		var = (t_dict *) env->content;
		if (var->value)
		{
			ft_putstr_fd(var->key, cmd->fd[1]);
			ft_putstr_fd("=", cmd->fd[1]);
			ft_putstr_fd(var->value, cmd->fd[1]);
			ft_putstr_fd("\n", cmd->fd[1]);
		}
		env = env->next;
	}
	return (0);
}
