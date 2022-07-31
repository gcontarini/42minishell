/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:02:54 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/31 16:05:46 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_cmd *cmd, t_shell *sh)
{
	t_dict	*var;
	t_list	*var_node;
	int		pos;

	pos = 1;
	while (cmd->av[pos])
	{
		var = get_dict_var(cmd->av[pos], sh->env);
		if (var)
		{
			var_node = ft_lst_remove(&sh->env, var);
			free_dict(var);
			free(var_node);
		}
		pos++;
	}
	return (0);
}
