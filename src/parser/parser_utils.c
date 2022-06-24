/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:27:27 by gcontari          #+#    #+#             */
/*   Updated: 2022/06/24 13:45:12 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_arr(void *arr)
{
	void	**tmp;

	tmp = (void **) arr;
	while (*tmp)
		free(*tmp++);
	free(arr);
	return (NULL);
}

void	*xmc(void *p, void *mem)
{
	if (p)
		return (p);
	free(mem);
	exit(1);
	return (NULL);
}

void	*xmalloc(size_t size, void *mem, t_shell sh)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr)
		return (ptr);
	if (mem)
		free(mem);
	if (sh.env)
		free(sh.env);
	if (sh.input)
		free(sh.input);
	// if (sh.token_list)
	// 	// free(sh.token_list); // Proper implement a free function
	// if (sh.cmd_list)
	// 	// free(sh.cmd_list); // Proper implement a free function
	exit(1);
	return (NULL);
}

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
