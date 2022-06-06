/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:01:37 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/06 16:29:43 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_cmd_out(t_cmd *cmd);
static int	add_cmd_in(t_cmd *cmd);

int	add_cmd_in_out(t_cmd *cmd)
{
	add_cmd_in(cmd);
	add_cmd_out(cmd);
	return (0);
}

static int	add_cmd_out(t_cmd *cmd)
{
	t_list	*curr_token;
	void	*curr_cont;

	curr_token = cmd->token_list;
	while (curr_token)
	{
		curr_cont = (char *)curr_token->content;
		if (ft_strncmp("|", curr_cont, 2) == 0
			&& !cmd->out.fname)
				cmd->out.fname = curr_cont;
		else if ((ft_strncmp(">", curr_cont, 2) == 0
				|| (ft_strncmp(">>", curr_cont, 3) == 0))
			&& !cmd->out.fname)
		{
			if (curr_token->next)
			{
				cmd->out.fname = (char *)curr_token->next->content;
				cmd->out.redirection = curr_cont;
			}
			// else error
		}
		curr_token = curr_token->next;
	}
	return (0);
}

static int	add_cmd_in(t_cmd *cmd)
{
	t_list	*curr_token;
	void	*curr_cont;

	curr_token = cmd->token_list;
	while (curr_token)
	{
		curr_cont = (char *)curr_token->content;
		if ((ft_strncmp("<", curr_cont, 2) == 0
				|| (ft_strncmp("<<", curr_cont, 3) == 0))
			&& !cmd->in.fname)
		{
			if (curr_token->next)
			{
				cmd->in.fname = (char *)curr_token->next->content;
				cmd->in.redirection = curr_cont;
				curr_token = curr_token->next;
			}
			// else error
		}
		curr_token = curr_token->next;
	}
	return (0);
}

char	**add_cmd_av(t_cmd *cmd)
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
