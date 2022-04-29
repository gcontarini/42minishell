/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:59:38 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/29 15:59:18 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**llist_n_to_av(t_list *llist, int ac);
static int	add_new_cmd(t_list **cmd_list, t_list *token_list);

t_list	*get_cmd_list(char *input)
{
	t_list	*cmd_list; // need to be dynamic allocation
	t_list	*token_list;
	t_list	*head;

	token_list = NULL;
	get_token_list(input, &token_list); // need to add a check if it fails
	// need to check how many command are there (count_comm or something like that)
	// while loop to assign all the commands
	cmd_list = NULL;
	head = token_list;
	while (head)
	{
		add_new_cmd(&cmd_list, head);
		head = head->next;
	}
	ft_lstclear(&token_list, NULL);
	return (cmd_list);
}

static int	add_new_cmd(t_list **cmd_list, t_list *token_list)
{
	t_list	*head;
	t_list	*new_node;
	t_cmd	new_cmd;
	int		argc;

	new_cmd.in.fname = NULL;
	new_cmd.out.fname = NULL;
	argc = 0;
	head = token_list;
	while (head) // && is_cmd_sep(head)
	{
		// check if there are riderections to files 
		//		change in and out accordingly in case
		argc++;
		head = head->next;
	}
	new_cmd.av = llist_n_to_av(token_list, argc);
	if (new_cmd.av == NULL)
		return (-1);
	new_node = ft_lstnew(&new_cmd);
	if (!new_node)
		return (-1);
	ft_lstadd_back(cmd_list, new_node);
	return (0);
}

static char	**llist_n_to_av(t_list *llist, int argc)
{
	char	**av;
	t_list	*head;
	int		pos;

	av = malloc(sizeof(*av) * (argc + 1));
	if (!av)
		return (NULL);
	head = llist;
	pos = 0;
	while (pos < argc && head)
	{
		av[pos] = head->content;
		head = head->next;
		pos++;
	}
	av[pos] = NULL;
	return (av);
}