/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:01:37 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/17 20:18:19 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(const char *str);

void	add_cmd_in_out(t_cmd *cmd, t_list *curr_token, t_shell *sh)
{
	t_token	*curr_cont;
	t_dict	*fd_pair;

	while (curr_token)
	{
		curr_cont = (t_token *) curr_token->content;
		if (is_redirection(curr_cont->s))
		{
			fd_pair = xmc(ft_calloc(sizeof(t_dict), 1), NULL, 0, *sh);
			fd_pair->key = curr_cont->s;
			if (ft_strncmp("|", curr_cont->s, 2))
			{
				if (curr_token->next)
					fd_pair->value = ((t_token *) curr_token->next->content)->s;
				else
					sh->exit_status = 258;
			}
			ft_lstadd_back(&cmd->fd_pair_list, xmc(ft_lstnew(fd_pair), NULL, 0, *sh));
		}
		curr_token = curr_token->next;
	}
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
			ft_lstdelone(ft_lst_remove(tlist, curr_t->next->content), free_t);
			ft_lstdelone(ft_lst_remove(tlist, curr_t->content), free_t);
			curr_t = tmp;
		}
		else if (ft_strncmp("|", ((t_token *) curr_t->content)->s, 2) == 0)
		{
			tmp = curr_t->next;
			ft_lstdelone(ft_lst_remove(tlist, curr_t->content), free_t);
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
		"|", "<", ">", "<<", ">>", NULL
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
