/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:24:43 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/28 16:26:13 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h" 

# define METACHAR_SET "|&;()<>"
# define SPACE_SET " \n\t"

typedef struct s_comm_list
{
	char				**av;
	int					input;
	int					output;
	struct s_comm_list	*next;
}	t_comm_list;

void	get_token_list(char *input, t_list **token_list);

#endif