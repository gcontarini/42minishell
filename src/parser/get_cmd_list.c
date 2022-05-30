/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:59:38 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/30 17:41:14 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*add_new_cmd(t_list **cmd_list, t_list *token_list);
static t_cmd	*init_new_cmd(void);
static t_list	*add_cmd_token_list(t_list *token_list, int argc);
static int		add_cmd_in_out(t_cmd *cmd);

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
	argc = 0;
	head = token_list;
	while (head)
	{
		if (is_control_operator(head->content))
		{
			argc++;
			head = head->next;
			break ;
		}
		argc++;
		head = head->next;
	}
	new_cmd->token_list = add_cmd_token_list(token_list, argc);
	error_check(add_cmd_in_out(new_cmd));
	new_cmd->av = llist_to_av(new_cmd->token_list);
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
	new_cmd->in.fd = -1;
	new_cmd->out.fd = -1;
	new_cmd->av = NULL;
	return (new_cmd);
}

static t_list	*add_cmd_token_list(t_list *token_list, int argc)
{
	t_list	*head;

	head = token_list;
	while (head && argc > 1)
	{
		argc--;
		head = head->next;
	}
	if (head)
		head->next = NULL;
	return (token_list);
}

static int	add_cmd_in_out(t_cmd *cmd)
{
	t_list	*head;

	head = cmd->token_list;
	while (head)
	{
		if (ft_strncmp("|", (char *)head->content, 2) == 0
			&& !cmd->out.fname)
		{
			cmd->out.fname = (char *)head->content;
			// remove token from cmd->token_list
		}
		else if (ft_strncmp(">", (char *)head->content, 2) == 0
			&& !cmd->out.fname)
		{
			if (head->next)
			{
				cmd->out.fname = (char *)head->next->content;
				// remove this and next token from cmd->token_list
			}
			// else error
		}
		else if (ft_strncmp("<", (char *)head->content, 2) == 0
			&& !cmd->in.fname)
		{
			if (head->next)
			{
				cmd->in.fname = (char *)head->next->content;
				// remove this and next token from cmd->token_list
			}
			// else error
		}
		head = head->next;
	}
	return (0);
}
