/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_grammar_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 20:00:15 by gcontari          #+#    #+#             */
/*   Updated: 2022/08/02 08:57:26 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*syntax_error(char *err_msg, t_shell *sh);
static t_uint	apply_next_rule(t_ttype curr, t_ttype next);
static t_uint	apply_last_rule(t_ttype curr);

t_list	*syntax_error_checker(t_list *curr, t_shell *sh)
{
	t_token	*token_curr;
	t_token	*token_next;

	token_curr = (t_token *) curr->content;
	if (curr->next)
	{
		token_next = (t_token *) curr->next->content;
		if (apply_next_rule(token_curr->t, token_next->t))
			return (syntax_error(ERRMSG_SYNTAX, sh));
	}
	else if (apply_last_rule(token_curr->t))
		return (syntax_error(ERRMSG_OPEN_REDIR, sh));
	return (curr);
}

static t_list	*syntax_error(char *err_msg, t_shell *sh)
{
	ft_lstclear(&(sh->token_list), free_token);
	ms_exit(2, err_msg, false, sh);
	return (NULL);
}

static t_uint	apply_next_rule(t_ttype curr, t_ttype next)
{
	return ((curr >= CON_REDIR && next >= CON_PIPE)
		+ ((curr == CON_PIPE || curr == I_PIPE)
			&& (next == CON_PIPE || next == I_PIPE)));
}

static t_uint	apply_last_rule(t_ttype curr)
{
	return (curr >= CON_PIPE);
}
