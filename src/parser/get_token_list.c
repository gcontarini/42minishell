/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:44:00 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/29 16:28:06 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_metachar(char c);
static int	is_space(char c);
static char	*get_next_token(char *input);


int	get_token_list(char *input, t_list **token_list)
{
	char	*new_token;
	t_list	*new_token_el;
	int		pos;
	int		flag;

	pos = 0;
	flag = 0; // use to track errors - there might be a better way
	while (input[pos] && is_space(input[pos]))
		pos++;
	new_token = get_next_token(&input[pos]);
	if (new_token)
	{
		new_token_el = ft_lstnew(new_token);
		if (new_token_el)
			ft_lstadd_back(token_list, new_token_el);
		pos += ft_strlen(new_token);
		return (get_token_list(&input[pos], token_list));
	}
	return (flag);
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
			while(input[len]
				&& !is_space(input[len]) && is_metachar(input[len]))
				len++;
		}
		else
		{
			while (input[len]
				&& !is_space(input[len]) && !is_metachar(input[len]))
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