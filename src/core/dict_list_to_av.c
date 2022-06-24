/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_list_to_av.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:32:13 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/18 17:32:55 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dict_to_str(t_dict *var);

char	**dict_list_to_av(t_list *dict_list)
{
	char	**array_string;
	int		lst_size;
	int		pos;

	lst_size = ft_lstsize(dict_list);
	array_string = error_check_pointer(malloc(sizeof(char *)
				* (lst_size + 1)));
	pos = 0;
	while (dict_list && pos < lst_size)
	{
		array_string[pos] = dict_to_str((t_dict *) dict_list->content);
		dict_list = dict_list->next;
		pos++;
	}
	array_string[pos] = NULL;
	return (array_string);
}

static char	*dict_to_str(t_dict *var)
{
	char	*str;
	size_t	tot_len;

	tot_len = ft_strlen(var->key) + ft_strlen(var->value) + 2;
	str = error_check_pointer(malloc(sizeof(char) * tot_len));
	ft_strlcpy(str, var->key, ft_strlen(var->key) + 1);
	ft_strlcat(str, "=", ft_strlen(str) + 2);
	ft_strlcat(str, var->value, ft_strlen(str) + ft_strlen(var->value) + 1);
	return (str);
}
