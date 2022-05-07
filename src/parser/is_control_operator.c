/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_control_operator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 09:50:49 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/07 10:53:59 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// control operator list
// "||", "&&", "&", ";" ";;" ";&", ";;&", "|", "|&", "(", ")"
// ; and & are not to be considered

int	is_control_operator(void *void_token)
{
	char	*token;

	token = (char *) void_token;
	if (ft_strchr("|", *token))
	// compare with possible options 
	// if matching (ft_strncmp with option ft_strlen)
		return (1);
	return (0);
}
