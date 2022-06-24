/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:59:38 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/18 16:37:16 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*add_new_cmd(t_list **cmd_list, t_list *token_list);
static t_cmd	*init_new_cmd(void);
static t_list	*split_llist(t_list *llist, int argc);
// utils
int				add_cmd_in_out(t_cmd *cmd);
char			**add_cmd_av(t_cmd *cmd);
int				control_operator_pos(t_list *llist);
t_list			*llist_pos(t_list *llist, int pos);

t_list	*get_cmd_list(t_list *token_list)
{
	t_list	*cmd_list;
	t_list	*head;

	cmd_list = NULL;
	head = token_list;
	while (head)
		head = add_new_cmd(&cmd_list, head);
	return (cmd_list);
}

static t_list	*add_new_cmd(t_list **cmd_list, t_list *token_list)
{
	t_list	*head;
	t_list	*new_node;
	t_cmd	*new_cmd;
	int		argc;

	new_cmd = init_new_cmd();
	argc = control_operator_pos(token_list);
	head = llist_pos(token_list, (argc + 1));
	new_cmd->token_list = split_llist(token_list, argc + 1);
	error_check(add_cmd_in_out(new_cmd));
	new_cmd->av = add_cmd_av(new_cmd);
	new_node = (t_list *)error_check_pointer(ft_lstnew(new_cmd));
	ft_lstadd_back(cmd_list, new_node);
	return (head);
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
