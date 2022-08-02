/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 20:00:15 by gcontari          #+#    #+#             */
/*   Updated: 2022/08/02 08:52:42 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		concat_next(t_list *curr, t_shell *sh);
static void		remove_empty(t_list *head, t_list *curr, t_shell *sh);

t_list	*build_syntax_tree(t_shell *sh)
{
	t_list	*curr;
	t_token	*token;

	if (ft_strlen(((t_token *) sh->token_list->content)->s) == 0)
		remove_empty(sh->token_list, NULL, sh);
	curr = sh->token_list;
	while (curr->next)
	{
		token = (t_token *) curr->next->content;
		if (((t_token *) curr->content)->t < CON_PIPE
			&& token->t < CON_PIPE && token->t % 2 == 0)
			concat_next(curr, sh);
		else if (ft_strlen(token->s) == 0)
			remove_empty(sh->token_list, curr, sh);
		else
		{
			if (!syntax_error_checker(curr, sh))
				return (NULL);
			curr = curr->next;
		}
	}
	if (!syntax_error_checker(curr, sh))
		return (NULL);
	return (sh->token_list);
}

static void	concat_next(t_list *curr, t_shell *sh)
{
	t_token	*token_curr;
	t_token	*token_next;
	t_list	*list_tmp;
	char	*tmp;

	token_curr = (t_token *) curr->content;
	token_next = (t_token *) curr->next->content;
	tmp = token_curr->s;
	token_curr->s = xmc(
			ft_strjoin(token_curr->s, token_next->s), NULL, 0, sh);
	list_tmp = curr->next;
	curr->next = curr->next->next;
	free(tmp);
	ft_lstdelone(list_tmp, free_token);
}

static void	remove_empty(t_list *head, t_list *curr, t_shell *sh)
{
	t_list	*tmp;

	if (curr)
		tmp = (t_list *) curr->next;
	else
	{
		tmp = head;
		if (head && head->next)
			sh->token_list = head->next;
	}
	if (curr && curr->next)
		curr->next = curr->next->next;
	ft_lstdelone(tmp, free_token);
}
