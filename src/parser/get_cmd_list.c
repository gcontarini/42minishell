/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:59:38 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/25 16:04:25 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*pop_cmd_token_list(t_list **llist);
static t_cmd	*init_new_cmd(void);
static t_list	*split_llist(t_list *llist, int argc);
// utils
int				add_cmd_in_out(t_cmd *cmd, t_list *cmd_token_list);
char			**token_list_to_av(t_list **token_list, t_shell sh);
int				control_operator_pos(t_list *llist);
t_list			*llist_pos(t_list *llist, int pos);

t_list	*get_cmd_list(t_list **token_list, t_shell sh)
{
	t_list	*cmd_list;
	t_list	*cmd_token_list;
	t_list	*tmp;
	t_cmd	*next_cmd;

	cmd_list = NULL;
	cmd_token_list = pop_cmd_token_list(token_list);
	while (cmd_token_list)
	{
		next_cmd = xmc(init_new_cmd(), NULL, 0, sh);
		add_cmd_in_out(next_cmd, cmd_token_list);
		// if fails - break execution and went back to reading
		next_cmd->av = token_list_to_av(&cmd_token_list, sh);
		tmp = cmd_token_list;
		cmd_token_list = pop_cmd_token_list(token_list);
		ft_lstclear(&tmp, NULL);
		ft_lstadd_back(&cmd_list, xmc(ft_lstnew(next_cmd), NULL, 0, sh));
	}
	return (cmd_list);
}

static t_list	*pop_cmd_token_list(t_list **llist)
{
	t_list	*prev_head;
	int		new_head_pos;

	new_head_pos = 0;
	prev_head = NULL;
	if (*llist)
	{
		new_head_pos = control_operator_pos(*llist) + 1;
		prev_head = *llist;
		*llist = llist_pos(*llist, new_head_pos);
	}
	return (split_llist(prev_head, new_head_pos));
}

static t_cmd	*init_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *) error_check_pointer(malloc(sizeof(t_cmd) * 1));
	new_cmd->in.fname = NULL;
	new_cmd->out.fname = NULL;
	new_cmd->in.redirection = NULL;
	new_cmd->out.redirection = NULL;
	new_cmd->in.fd = -1;
	new_cmd->out.fd = -1;
	new_cmd->av = NULL;
	return (new_cmd);
}

static t_list	*split_llist(t_list *llist, int argc)
{
	t_list	*head;

	head = llist;
	while (head && argc > 1)
	{
		argc--;
		head = head->next;
	}
	if (head)
		head->next = NULL;
	return (llist);
}

t_list	*llist_pos(t_list *llist, int pos)
{
	while (llist && pos > 0)
	{
		llist = llist->next;
		pos--;
	}
	return (llist);
}
