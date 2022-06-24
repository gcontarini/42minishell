/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dict_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:10:37 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/20 18:13:00 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*get_dict_var(const char *key, t_list *dict)
{
	t_dict	*var;

	while (dict && key)
	{
		var = (t_dict *) dict->content;
		if (ft_strncmp(key, var->key, ft_strlen(key) + 1) == 0)
			return (var);
		dict = dict->next;
	}
	return (NULL);
}
