/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_list_to_av.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:32:13 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/31 16:06:08 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dict_to_str(t_dict *var, t_shell *sh);

char	**dict_list_to_av(t_list *dict_list, t_shell *sh)
{
	char	**array_string;
	int		lst_size;
	int		pos;

	lst_size = ft_lstsize(dict_list);
	array_string = xmc(malloc(sizeof(char *) * (lst_size + 1)), NULL, 0, sh);
	pos = 0;
	while (dict_list && pos < lst_size)
	{
		array_string[pos] = dict_to_str((t_dict *) dict_list->content, sh);
		dict_list = dict_list->next;
		pos++;
	}
	array_string[pos] = NULL;
	return (array_string);
}

static char	*dict_to_str(t_dict *var, t_shell *sh)
{
	char	*str;
	size_t	tot_len;

	tot_len = ft_strlen(var->key) + ft_strlen(var->value) + 2;
	str = xmc(malloc(sizeof(char) * tot_len), NULL, 0, sh);
	ft_strlcpy(str, var->key, ft_strlen(var->key) + 1);
	ft_strlcat(str, "=", ft_strlen(str) + 2);
	if (var->value)
		ft_strlcat(str, var->value, ft_strlen(str) + ft_strlen(var->value) + 1);
	return (str);
}
