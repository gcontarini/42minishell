/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:16:55 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/01 17:18:29 by gcontari         ###   ########.fr       */
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
	// build_syntax_tree(sh.token_list, sh);
	return (sh.token_list);
}
