/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:16:55 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/01 20:17:37 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parser(t_shell *sh, const char *inpt)
{
	char	*inpt_exp;

	inpt_exp = expander(*sh, inpt);
	free((char *) inpt);
	sh->input = inpt_exp;
	sh->token_list = lexer(*sh, inpt_exp);
	// sh->token_list = build_syntax_tree(sh);
	return (sh->token_list);
}

// static t_list	*build_syntax_tree(t_shell sh)
// {
// 	t_list	*head;
// 	t_list	*curr;
// 	t_token	*token;

// 	// RULES -> TOKEN REDIR QUOTE
// 	head = sh.token_list;
// 	curr = head;
// 	while (curr)
// 	{
// 		token = (t_token *) curr->content;

// 		curr = curr->next;
// 	}
// 	return (head);
// }
