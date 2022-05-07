/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:59:38 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/07 10:55:47 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**llist_n_to_av(t_list *llist, int ac);
static t_list	*add_new_cmd(t_list **cmd_list, t_list *token_list);
static t_cmd	*init_new_cmd(void);

t_list	*get_cmd_list(char *input)
{
	t_list	*cmd_list;
	t_list	*token_list;
	t_list	*head;

	token_list = NULL;
	cmd_list = NULL;
	error_check(get_token_list(input, &token_list));
	// exepand tokens
	head = token_list;
	while (head)
		head = add_new_cmd(&cmd_list, head);
	// need to clean list (but not content) memory allocated
	// ft_lstclear(&token_list, NULL); this creates segfault
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
		argc++;
		head = head->next;
		if (is_control_operator(head->content))
		{
			argc++;
			break ;
		}
	}
	new_cmd->av = (char **)error_check_pointer(llist_n_to_av(token_list, argc));
	// update cmd t_fd according to arguments
	new_node = (t_list *)error_check_pointer(ft_lstnew(new_cmd));
	ft_lstadd_back(cmd_list, new_node);
	return (head);
}

static char	**llist_n_to_av(t_list *llist, int argc)
{
	char	**av;
	t_list	*head;
	int		pos;

	av = (char **)error_check_pointer(malloc(sizeof(char *) * (argc + 1)));
	head = llist;
	pos = 0;
	while (pos < argc && head)
	{
		av[pos] = (char *) head->content;
		head = head->next;
		pos++;
	}
	av[pos] = NULL;
	return (av);
}

static t_cmd	*init_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *) error_check_pointer(malloc(sizeof(t_cmd) * 1));
	new_cmd->in.fname = NULL;
	new_cmd->out.fname = NULL;
	return (new_cmd);
}
