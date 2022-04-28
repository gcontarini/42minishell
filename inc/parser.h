/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:24:43 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/28 17:40:18 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h" 

# define METACHAR_SET "|&;()<>"
# define SPACE_SET " \n\t"s

void	get_token_list(char *input, t_list **token_list);
t_cmd	*get_comm_list(char *input);

#endif