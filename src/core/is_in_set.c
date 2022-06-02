/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:06:07 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/02 16:06:53 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_set(char *str, char **set)
{
	int	pos;

	if (!set)
		return (0);
	pos = 0;
	while (set[pos])
	{
		if (ft_strncmp(str, set[pos], ft_strlen(set[pos]) + 1) == 0)
			return (1);
		pos++;
	}
	return (0);
}
