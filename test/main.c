/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:54:57 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/21 18:57:18 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	// char	*inpt;

	// register_signals();
	// while (1)
	// {
	// 	inpt = readline("HELLO ");
	// 	printf("%s\n", inpt);
	// }
	printf("%d\n", ttyslot());
	printf("%d\n", STDIN_FILENO);
	return (0);
}
