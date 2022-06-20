/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_dict.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:17:55 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/20 18:32:40 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*str_to_dict(char *str)
{
	t_dict	*var;
	size_t	len_key;
	char	*value;

	var = error_check_pointer(ft_calloc(1, sizeof(t_dict)));
	if (ft_strchr(str, '='))
	{
		value = ft_strchr(str, '=') + 1;
		var->value = error_check_pointer(ft_strndup(value, ft_strlen(value)));
		len_key = ft_strlen(str) - ft_strlen(value) - 1;
		var->key = error_check_pointer(ft_strndup(str, len_key));
	}
	else
		var->key = ft_strndup(str, ft_strlen(str));
	return (var);
}
