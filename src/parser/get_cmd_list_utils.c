/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:01:37 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/26 20:52:25 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_cmd_out(t_cmd *cmd, t_list *cmd_token_list);
static int	add_cmd_in(t_cmd *cmd, t_list *cmd_token_list, t_shell *sh);
static int	is_redirection(const char *str);

char		*ft_replace(char *original, char *new);

int	add_cmd_in_out(t_cmd *cmd, t_list *cmd_token_list, t_shell *sh)
{
	int	return_status;

	return_status = 0;
	return_status = add_cmd_in(cmd, cmd_token_list, sh);
	if (return_status == 0)
		return_status = add_cmd_out(cmd, cmd_token_list);
	return (return_status);
}

static t_fd	update_fd_out(t_fd curr_out, t_token *curr_cont, t_list *curr_token)
{
	t_fd	out;
	int		tmp_fd;
	int		open_flags;

	out.fname = NULL;
	out.red = NULL;
	if (curr_token->next)
	{
		if (curr_out.fname != NULL)
		{
			if (ft_strncmp(curr_out.red, ">", 2) == 0)
				open_flags = O_WRONLY | O_CREAT | O_TRUNC;
			else
				open_flags = O_WRONLY | O_APPEND | O_CREAT;
			tmp_fd = open(curr_out.fname, open_flags, 0622);
			close(tmp_fd);
		}
		out.fname = ft_replace(curr_out.fname,
				((t_token *) curr_token->next->content)->s);
		out.red = ft_replace(curr_out.red,
				curr_cont->s);
		return (out);
	}
	out.fd = -256;
	return (out);
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
			cmd->out = update_fd_out(cmd->out, curr_cont, curr_token);
			if (cmd->out.fd == -256)
				return (258);
		}
		curr_token = curr_token->next;
	}
	return (0);
}

static t_fd	update_fd_in(t_fd curr_in, t_token *curr_cont, t_list *curr_token,
	t_shell *sh)
{
	t_fd	in;
	int		tmp_fd;

	in.fname = NULL;
	in.red = NULL;
	if (curr_token->next)
	{
		if (curr_in.fname != NULL)
		{
			if (ft_strncmp(curr_in.red, "<", 2) == 0)
				tmp_fd = open(curr_in.fname, O_RDONLY);
			else
				tmp_fd = here_doc(curr_in.fname, sh);
			close(tmp_fd);
		}
		in.fname = ft_replace(curr_in.fname,
				((t_token *) curr_token->next->content)->s);
		in.red = ft_replace(curr_in.red,
				curr_cont->s);
		if (tmp_fd != -1)
			return (in);
	}
	in.fd = -256;
	return (in);
}

static int	add_cmd_in(t_cmd *cmd, t_list *cmd_token_list, t_shell *sh)
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
			cmd->in = update_fd_in(cmd->in, curr_cont, curr_token, sh);
			if (cmd->in.fd == -256)
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
