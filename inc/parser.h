/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:24:43 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/28 15:32:28 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSERS_H
# define PARSERS_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h" 

# define METACHAR_SET "|&;()<>"
# define SPACE_SET " \n\t"

typedef struct s_comm_list
{
	char					**av;
	int						input;
	int						output;
	struct s_comm_list	*next;
} t_comm_list;

void	get_token_list(char *input, t_list **token_list);

#endif