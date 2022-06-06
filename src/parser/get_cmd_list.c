/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:59:38 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/06 15:55:01 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*add_new_cmd(t_list **cmd_list, t_list *token_list);
static t_cmd	*init_new_cmd(void);
static t_list	*add_cmd_token_list(t_list *token_list, int argc);
static int		add_cmd_in_out(t_cmd *cmd);
static char		**add_cmd_av(t_cmd *cmd);

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
	void	*curr_cont;

	head = cmd->token_list;
	while (head)
	{
		curr_cont = (char *)head->content;
		if (ft_strncmp("|", curr_cont, 2) == 0)
		{
			if (!cmd->out.fname)
				cmd->out.fname = curr_cont;
		}
		else if (ft_strncmp(">", curr_cont, 2) == 0
			&& !cmd->out.fname)
		{
			if (head->next)
			{
				cmd->out.fname = (char *)head->next->content;
				cmd->out.redirection = curr_cont;
			}
			// else error
		}
		else if (ft_strncmp("<", curr_cont, 2) == 0
			&& !cmd->in.fname)
		{
			if (head->next)
			{
				cmd->in.fname = (char *)head->next->content;
				cmd->in.redirection = curr_cont;
			}
			// else error
		}
		head = head->next;
	}
	return (0);
}

static char	**add_cmd_av(t_cmd *cmd)
{
	t_list	*curr_token;
	t_list	*tmp;

	curr_token = cmd->token_list;
	while (curr_token)
	{
		if (ft_strncmp("<", (char *) curr_token->content, 2) == 0
			|| ft_strncmp(">", (char *) curr_token->content, 2) == 0)
		{
			tmp = curr_token->next->next;
			free(ft_lst_remove(&cmd->token_list, curr_token->next->content));
			free(ft_lst_remove(&cmd->token_list, curr_token->content));
			curr_token = tmp;
		}
		else
		{
			if (ft_strncmp("|", (char *) curr_token->content, 2) == 0)
				free(ft_lst_remove(&cmd->token_list, curr_token->content));
			curr_token = curr_token->next;
		}
	}
	return (llist_to_av(cmd->token_list));
}
