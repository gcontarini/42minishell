/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_control_operator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 09:50:49 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/05 17:01:20 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// control operator list
// "||", "&&", "&", ";" ";;" ";&", ";;&", "|", "|&", "(", ")"

int	is_control_operator(void *void_token)
{
	size_t	token_size;
	char	*token;

	token = (char *) void_token;
	token_size = ft_strlen(token);
	if (token_size < 4)
	{
		if (ft_strchr("|&;", *token))
		// compare with possible options 
		// if matching (ft_strncmp with option ft_strlen)
			return (1);
	}
	return (0);
}
