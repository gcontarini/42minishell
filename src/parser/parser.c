/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:16:55 by gcontari          #+#    #+#             */
/*   Updated: 2022/06/28 10:11:11 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef enum e_token_type
// {
// 	BIN,
// 	FILE,
// 	R_DIR,
// 	L_DIR,
// 	PIPE,
// 	QUOTE,
// 	AND,
// 	OR,
// 	O_PAR,
// 	C_PAR
// }	t_ttype;

typedef enum e_token_type
{
	GENERAL,
	DIRECTION,
	QUOTE
}	t_ttype;
typedef struct s_token
{
	char	*s;
	enum	e_ttype;
}	t_token;

// Move structs to header.
// Add new enum types and free functions to xmc
// Write a main to test lexer

t_list	*parser(t_shell sh, const char *inpt)
{
	char	*inpt_exp;

	inpt_exp = expander(sh, inpt);
	sh.token_list = lexer(sh, inpt_exp);
	free(inpt_exp);
	return (sh.token_list);
}

// If this approch works well I will transform this if list in an function array with a selector
// Shoud I?
static t_list	*lexer(t_shell sh, const char *inpt)
{
	while (inpt && *inpt)
	{
		if (ft_strchr("\"\'", *inpt))
			inpt = quote_handler(inpt, sh.token_list, sh);
		else if (ft_strchr(METACHAR_SET, *inpt))
			inpt = dir_handler(inpt, sh.token_list, sh);
		else if (ft_strchr(SPACE_SET, *inpt))
			while (ft_strchr(SPACE_SET, *(++inpt)))
				;
		else
			inpt = normal_handler(inpt, sh.token_list, sh);
	}
	return (sh.token_list);
}

const char	*quote_handler(const char *inpt, t_list *head, t_shell sh)
{
	char		*token_str;
	char		*p;
	t_list		*node;
	t_token		*token;

	p = ft_strchr(inpt + 1, *inpt);
	if (!p)
		return (normal_handler(inpt, head, sh));
	token_str = xmc(ft_strndup(inpt + 1, p - inpt), NULL, 0, sh);
	token = xmc(new_token(token_str, QUOTE), token_str, T_MEM, sh);
	node = xmc(ft_lstnew(token), token, T_TOKEN, sh);
	ft_lstadd_back(sh.token_list, node);
	return (p + 1);
}

const char	*dir_handler(const char *inpt, t_list *head, t_shell sh)
{
	char		*p;
	t_uint		step;
	t_list		*node;
	t_token		*token;

	step = 1;
	if (*(inpt + 1) == *inpt)
		step++;
	p = xmc(ft_strndup(inpt, step), NULL, 0, sh);
	token = xmc(new_token(p, DIRECTION), p, T_MEM, sh);
	node = xmc(ft_lstnew(token), token, T_TOKEN, sh);
	ft_lstadd_back(sh.token_list, node);
	return (inpt + step);
}

const char	*normal_handler(const char *inpt, t_list *head, t_shell sh)
{
	char		*token_str;
	char		*p;
	t_list		*node;
	t_token		*token;

	p = inpt;
	while (*p && !ft_strchr(METACHAR_SET, *p))
		p++;
	token_str = xmc(ft_strndup(inpt + 1, p - inpt), NULL, 0, sh);
	token = xmc(new_token(token_str, GENERAL), token_str, T_MEM, sh);
	node = xmc(ft_lstnew(token), token, T_TOKEN, sh);
	ft_lstadd_back(sh.token_list, node);
	return (p);
}