/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:01:37 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/01 21:01:08 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_cmd_out(t_cmd *cmd, t_list *cmd_token_list);
static int	add_cmd_in(t_cmd *cmd, t_list *cmd_token_list);

int	add_cmd_in_out(t_cmd *cmd, t_list *cmd_token_list)
{
	int	return_status;

	return_status = 0;
	return_status = add_cmd_in(cmd, cmd_token_list);
	if (return_status == 0)
		return_status = add_cmd_out(cmd, cmd_token_list);
	return (return_status);
}

static int	add_cmd_out(t_cmd *cmd, t_list *cmd_token_list)
{
	t_list	*curr_token;
	t_token	*curr_cont;

	curr_token = cmd_token_list;
	while (curr_token)
	{
		curr_cont = (t_token *) curr_token->content;
		if (ft_strncmp("|", curr_cont->s, 2) == 0
			&& !cmd->out.fname)
				cmd->out.fname = curr_cont->s;
		else if ((ft_strncmp(">", curr_cont->s, 2) == 0
				|| (ft_strncmp(">>", curr_cont->s, 3) == 0))
			&& !cmd->out.fname)
		{
			if (curr_token->next)
			{
				cmd->out.fname = ((t_token *) curr_token->next->content)->s;
				cmd->out.redirection = curr_cont->s;
			}
			else
				return (258);
		}
		curr_token = curr_token->next;
	}
	return (0);
}

static int	add_cmd_in(t_cmd *cmd, t_list *cmd_token_list)
{
	t_list	*curr_token;
	t_token	*curr_cont;

	curr_token = cmd_token_list;
	while (curr_token)
	{
		curr_cont = (t_token *) curr_token->content;
		if ((ft_strncmp("<", curr_cont->s, 2) == 0
				|| (ft_strncmp("<<", curr_cont->s, 3) == 0))
			&& !cmd->in.fname)
		{
			if (curr_token->next)
			{
				cmd->in.fname = ((t_token *)curr_token->next->content)->s;
				cmd->in.redirection = curr_cont->s;
				curr_token = curr_token->next;
			}
			else
				return (258);
		}
		curr_token = curr_token->next;
	}
	return (0);
}

char	**token_list_to_av(t_list **token_list, t_shell sh)
{
	t_list	*curr_t;
	t_list	*tmp;

	curr_t = *token_list;
	while (curr_t)
	{
		if (ft_strncmp("<", ((t_token *) curr_t->content)->s, 2) == 0
			|| ft_strncmp(">", ((t_token *) curr_t->content)->s, 2) == 0)
		{
			tmp = curr_t->next->next;
			ft_lstdelone(ft_lst_remove(token_list, curr_t->next->content),
				free_token_wrap);
			ft_lstdelone(ft_lst_remove(token_list, curr_t->content),
				free_token_wrap);
			curr_t = tmp;
		}
		else if (ft_strncmp("|", ((t_token *) curr_t->content)->s, 2) == 0)
		{
			tmp = curr_t->next;
			ft_lstdelone(ft_lst_remove(token_list, curr_t->content),
				free_token_wrap);
			curr_t = tmp;
		}
		else
			curr_t = curr_t->next;
	}
	return (xmc(llist_to_av(*token_list, sh), NULL, 0, sh));
}
