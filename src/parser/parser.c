/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:16:55 by gcontari          #+#    #+#             */
/*   Updated: 2022/06/27 09:24:52 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parser(t_shell sh, const char *inpt)
{
	char	*inpt_exp;
	t_list	*head;

	inpt_exp = expander(sh, inpt);
	head = _parser(sh, inpt_exp);
	return (head);
}

static t_list	*_parser(t_shell sh, const char *inpt)
{


}
