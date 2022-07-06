/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:16:55 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/06 09:38:16 by gcontari         ###   ########.fr       */
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
	sh->token_list = build_syntax_tree(sh);
	return (sh->token_list);
}

t_list	*build_syntax_tree(t_shell *sh)
{
	t_list	*curr;
	t_token	*token;

	curr = sh->token_list->next;
	while (curr)
	{
		// Need to save last node and current one
		// Change both functions to cover that
		token = (t_token *) curr->content;
		if (token->t < CON_REDIR && token->t % 2 == 0)
			concat_last(sh->token_list, curr, sh);
		// token = (t_token *) curr->content;
		if (ft_strlen(token->s) == 0)
			remove_empty(sh->token_list, curr, sh);
		curr = curr->next;
	}
	return (sh->token_list);
}

static void	concat_last(t_list *head, t_list *curr, t_shell *sh)
{

}

static void	remove_empty(t_list *head, t_list *curr, t_shell *sh)
{

}
