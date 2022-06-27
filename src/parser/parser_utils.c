/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:27:27 by gcontari          #+#    #+#             */
/*   Updated: 2022/06/27 09:27:01 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_uint	str_count_char(const char *s, char c)
{
	t_uint	i;

	i = 0;
	while (s && *s)
	{
		if (*s++ == c)
			i++;
	}
	return (i);
}
