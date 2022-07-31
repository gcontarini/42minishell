/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:14:41 by gcontarini        #+#    #+#             */
/*   Updated: 2022/07/31 16:08:18 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	static t_shell	sh;

	sh = init_shell(envp);
	if (ac > 1)
		shell_from_file(ac, av, &sh);
	else
		shell_interactive(&sh);
	return (0);
}
