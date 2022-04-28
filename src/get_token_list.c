/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:44:00 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/28 12:50:06 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_metachar(char c);
static int	is_space(char c);
static char	*get_next_token(char *input);


void	get_token_list(char *input, t_list **token_list)
{
	char	*new_token;
	t_list	*new_token_el;

	while (*input && is_space(*input))
		input++;
	new_token = get_next_token(input);
	if (new_token)
	{
		new_token_el = ft_lstnew(new_token);
		if (new_token_el)
			ft_lstadd_back(token_list, new_token_el);
		input += ft_strlen(new_token);
		return (get_token_list(input, token_list));
	}
	return ;
}

static char	*get_next_token(char *input)
{
	int		len;
	char	*token;

	if (*input)
	{
		len = 0;
		if (is_metachar(*input))
		{
			while(input[len] && !is_space(input[len]) && is_metachar(input[len]))
				len++;
		}
		else
		{
			while (input[len] && !is_space(input[len]) && !is_metachar(input[len]))
				len++;
		}
		token = ft_strndup(input, len);
		if (token)
			return (token);
	}
	return (NULL);
}

static int	is_space(char c)
{
	int pos;

	pos = 0;
	while (SPACE_SET[pos])
	{
		if (SPACE_SET[pos] == c)
			return (1);
		pos++;
	}
	return (0);
}
static int	is_metachar(char c)
{
	int pos;

	pos = 0;
	while (METACHAR_SET[pos])
	{
		if (METACHAR_SET[pos] == c)
			return (1);
		pos++;
	}
	return (0);
}