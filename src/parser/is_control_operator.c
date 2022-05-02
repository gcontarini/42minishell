/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_control_operator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 09:50:49 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/02 10:49:46 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// "||", "&&", "&", ";" ";;" ";&", ";;&", "|", "|&", "(", ")"

int	is_control_operator(char *token)
{
	size_t	token_size;

	token_size = ft_strlen(token);	
	if (token_size < 4)
	{
		// compare with possible options 
		// if matching (ft_strncmp with option ft_strlen)
		return (1);
	}
	return (0);
}
