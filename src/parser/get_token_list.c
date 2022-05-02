/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:44:00 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/02 12:29:16 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_next_token(const char *input);


int	get_token_list(const char *input, t_list **token_list)
{
	char	*new_token;
	t_list	*new_token_el;
	int		pos;
	int		flag;

	pos = 0;
	flag = 0; // use to track errors - there might be a better way
	while (input[pos] && ft_strchr(SPACE_SET, input[pos]))
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

static char	*get_next_token(const char *input)
{
	int		len;
	char	*token;

	if (*input)
	{
		len = 0;
		if (ft_strchr(METACHAR_SET, *input))
			len++;
			// if doing bonus need to check for control operators 
			// that can have more than 1 char
		// else if (ft_strchr("'\"", *input))
			// len = till the next quote
			//		when required, do the expansion
		else
		{
			while (input[len]
				&& !ft_strchr(SPACE_SET, input[len])
				&& !ft_strchr(METACHAR_SET, input[len]))
				len++;
		}
		token = ft_strndup(input, len);
		if (token)
			return (token);
	}
	return (NULL);
}
