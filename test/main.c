/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:54:57 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/29 16:33:46 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	t_list	*token_list;
	t_list	*cmd_list;
	t_list	*head;
	char	input[] = "asdf asf asdf &asdf&;asdf ";

	token_list = NULL;
	if (get_token_list(input, &token_list) == -1)
		return (1);
	cmd_list = get_cmd_list(input);
	head = token_list;
	while (token_list)
	{
		printf("%s\n", token_list->content);
		token_list = token_list->next;
	}
	ft_lstclear(&head, free);
	return (0);
}