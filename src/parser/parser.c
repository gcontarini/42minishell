/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:16:55 by gcontari          #+#    #+#             */
/*   Updated: 2022/06/29 09:55:30 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Write a main to test lexer
t_list	*parser(t_shell sh, const char *inpt)
{
	char	*inpt_exp;

	inpt_exp = expander(sh, inpt);
	free(inpt);
	sh.input = inpt_exp;
	sh.token_list = lexer(sh, inpt_exp);
	return (sh.token_list);
}

// If this approch works well I will transform this if list in an function array with a selector
// Shoud I?
static t_list	*lexer(t_shell sh, const char *inpt)
{
	while (inpt && *inpt)
	{
		while (*inpt && ft_strchr(SPACE_SET, *inpt))
			inpt++;
		if (*inpt && ft_strchr("\"\'", *inpt))
			inpt = quote_handler(inpt, sh);
		else if (*inpt && ft_strchr(METACHAR_SET, *inpt))
			inpt = dir_handler(inpt, sh);
		else if (*inpt)
			inpt = normal_handler(inpt, sh);
	}
	return (sh.token_list);
}

const char	*quote_handler(const char *inpt, t_shell sh)
{
	char		*p;

	p = ft_strchr(inpt + 1, *inpt);
	if (!p)
		return (normal_handler(inpt, sh));
	create_token(inpt + 1, p - inpt, sh);
	return (p + 1);
}

const char	*dir_handler(const char *inpt, t_shell sh)
{
	char		*p;
	t_uint		step;

	step = 1;
	if (*(inpt + 1) == *inpt)
		step++;
	create_token(inpt, step, sh);
	return (inpt + step);
}

const char	*normal_handler(const char *inpt, t_shell sh)
{
	char		*p;

	p = inpt;
	while (*p && !ft_strchr(EXP_SET, *p))
		p++;
	create_token(inpt + 1, p - inpt, sh);
	return (p);
}

static void	create_token(const char *str, t_uint n, t_shell sh)
{
	char		*token_str;
	t_list		*node;
	t_token		*token;

	token_str = xmc(ft_strndup(str, n), NULL, 0, sh);
	token = xmc(malloc(sizeof(t_token)), token_str, T_MEM, sh);
	token->s = token_str;
	node = xmc(ft_lstnew(token), token, T_TOKEN, sh);
	ft_lstadd_back(sh.token_list, node);
}
