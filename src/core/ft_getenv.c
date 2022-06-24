/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:04:31 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/20 18:20:54 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name, t_list *env)
{
	t_dict	*var;

	while (env)
	{
		var = (t_dict *) env->content;
		if (ft_strncmp(name, var->key, ft_strlen(name) + 1) == 0)
			return (var->value);
		env = env->next;
	}
	return (NULL);
}
