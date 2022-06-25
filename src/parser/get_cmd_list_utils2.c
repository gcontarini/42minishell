/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:56:01 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/25 15:56:26 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// control operator list
// "||", "&&", "&", ";" ";;" ";&", ";;&", "|", "|&", "(", ")"
// ; and & are not to be considered
int	is_control_operator(char *str)
{
	if (ft_strncmp("|", str, 2) == 0)
		return (1);
	return (0);
}

int	control_operator_pos(t_list *llist)
{
	char	*curr_content;
	int		pos;

	pos = 0;
	while (llist)
	{
		curr_content = (char *) llist->content;
		if (is_control_operator(curr_content))
			break ;
		pos++;
		llist = llist->next;
	}
	return (pos);
}
