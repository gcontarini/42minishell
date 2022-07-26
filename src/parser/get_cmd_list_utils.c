/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:01:37 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/26 12:32:47 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_cmd_out(t_cmd *cmd, t_list *cmd_token_list);
static int	add_cmd_in(t_cmd *cmd, t_list *cmd_token_list);
static int	is_redirection(const char *str);

char		*ft_replace(char *original, char *new);

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
			&& !cmd->out.red)
			cmd->out.red = ft_replace(cmd->out.red, curr_cont->s);
		else if ((ft_strncmp(">", curr_cont->s, 2) == 0
				|| (ft_strncmp(">>", curr_cont->s, 3) == 0)))
		{
			if (curr_token->next)
			{
				cmd->out.fname = ft_replace(cmd->out.fname,
						((t_token *) curr_token->next->content)->s);
				cmd->out.red = ft_replace(cmd->out.red,
						curr_cont->s);
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
				|| (ft_strncmp("<<", curr_cont->s, 3) == 0)))
		{
			if (curr_token->next)
			{
				cmd->in.fname = ft_replace(cmd->in.fname,
						((t_token *)curr_token->next->content)->s);
				cmd->in.red = ft_replace(cmd->in.red, curr_cont->s);
				curr_token = curr_token->next;
			}
			else
				return (258);
		}
		curr_token = curr_token->next;
	}
	return (0);
}

char	**token_list_to_av(t_list **tlist, t_shell sh)
{
	t_list	*curr_t;
	t_list	*tmp;

	curr_t = *tlist;
	while (curr_t)
	{
		if (is_redirection(((t_token *) curr_t->content)->s))
		{
			tmp = curr_t->next->next;
			ft_lstdelone(ft_lst_remove(tlist, curr_t->next->content),
				free_token);
			ft_lstdelone(ft_lst_remove(tlist, curr_t->content), free_token);
			curr_t = tmp;
		}
		else if (ft_strncmp("|", ((t_token *) curr_t->content)->s, 2) == 0)
		{
			tmp = curr_t->next;
			ft_lstdelone(ft_lst_remove(tlist, curr_t->content), free_token);
			curr_t = tmp;
		}
		else
			curr_t = curr_t->next;
	}
	return (xmc(llist_to_av(*tlist, sh), NULL, 0, sh));
}

static int	is_redirection(const char *str)
{
	static char	*red_set[] = {
		"<", ">", "<<", ">>", NULL
	};
	int			pos;

	pos = 0;
	while (red_set[pos])
	{
		if (ft_strncmp(red_set[pos], str, ft_strlen(red_set[pos]) + 1) == 0)
			return (1);
		pos++;
	}
	return (0);
}
