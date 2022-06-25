/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_dict.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:17:55 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/25 18:18:01 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*str_to_dict(char *str, t_shell sh)
{
	t_dict	*var;
	size_t	len_key;
	char	*value;

	var = xmc(ft_calloc(1, sizeof(t_dict)), NULL, 0, sh);
	if (ft_strchr(str, '='))
	{
		value = ft_strchr(str, '=') + 1;
		var->value = xmc(ft_strndup(value, ft_strlen(value)), NULL, 0, sh);
		len_key = ft_strlen(str) - ft_strlen(value) - 1;
		var->key = xmc(ft_strndup(str, len_key), NULL, 0, sh);
	}
	else
		var->key = ft_strndup(str, ft_strlen(str));
	return (var);
}
