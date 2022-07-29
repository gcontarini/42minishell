/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:56:01 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/29 17:11:59 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// control operator list
// "||", "&&", "&", ";" ";;" ";&", ";;&", "|", "|&", "(", ")"
// ; and & are not to be considered
int	is_control_operator(char *str)
{
	if (ft_strncmp("|", str, 2) == 0)
		return (1);
	return (0);
}

int	control_operator_pos(t_list *llist)
{
	char	*curr_content;
	int		pos;

	pos = 0;
	while (llist)
	{
		curr_content = ((t_token *) llist->content)->s;
		if (is_control_operator(curr_content))
			break ;
		pos++;
		llist = llist->next;
	}
	return (pos);
}

char	*ft_replace(char *original, char *new)
{
	if (original)
		free(original);
	return (ft_strndup(new, ft_strlen(new)));
}

int	is_redirection(const char *str)
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
