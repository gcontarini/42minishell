/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:19:39 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/31 18:46:15 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(void *av_void)
{
	int		pos;
	char	**av;

	av = (char **) av_void;
	pos = 0;
	while (av && av[pos])
	{
		if (av[pos])
			free(av[pos]);
		pos++;
	}
	free(av);
}

void	free_token(void *token_void)
{
	t_token	*token;

	token = (t_token *) token_void;
	if (token)
	{
		if (token->s)
			free(token->s);
		free(token);
	}
}

void	free_t(void *token_void)
{
	t_token	*token;

	token = (t_token *) token_void;
	if (token)
		free(token);
}
