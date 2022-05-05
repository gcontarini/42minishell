/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:59:38 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/05 16:09:13 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**llist_n_to_av(t_list *llist, int ac);
static t_list	*add_new_cmd(t_list **cmd_list, t_list *token_list);

t_list	*get_cmd_list(char *input)
{
	t_list	*cmd_list; // need to be dynamic allocation
	t_list	*token_list;
	t_list	*head;

	token_list = NULL;
	cmd_list = NULL;
	error_check(get_token_list(input, &token_list));
	// exepand tokens
	head = token_list;
	while (head)
		head = add_new_cmd(&cmd_list, head);
	// ft_lstclear(&token_list, NULL);
	return (cmd_list);
}

static t_list	*add_new_cmd(t_list **cmd_list, t_list *token_list)
{
	t_list	*head;
	t_list	*new_node;
	t_cmd	*new_cmd;
	int		argc;

	new_cmd = malloc(sizeof(t_cmd) * 1);
	if (!new_cmd)
		return (NULL);
	// add function to find input and output file descriptor
		// check if there are riderections to files 
		//		change in and out accordingly in case
		// check if it start with PIPE
	new_cmd->in.fname = NULL;
	new_cmd->out.fname = NULL;
	// count argv in the next command
	argc = 0;
	head = token_list;
	while (head && !is_control_operator(head->content))
	{
		// when encountering a pipe need to be sure that current cmd will 
		// write on PIPE and next cmd will read on PIPE (same one)
		argc++;
		head = head->next;
	}
	new_cmd->av = llist_n_to_av(token_list, argc);
	if (new_cmd->av == NULL)
		return (NULL);
	new_node = ft_lstnew(new_cmd);
	if (!new_node)
		return (NULL);
	ft_lstadd_back(cmd_list, new_node);
	return (head);
}

static char	**llist_n_to_av(t_list *llist, int argc)
{
	char	**av;
	t_list	*head;
	int		pos;

	av = malloc(sizeof(char *) * (argc + 1));
	if (!av)
		return (NULL);
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