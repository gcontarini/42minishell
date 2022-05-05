/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:54:57 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/05 17:05:50 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	cmd[] = "/Users/nprimo/Desktop/42minishell/b.out";
	char	*av[] = { "./b.out", NULL };
	pid_t	pid;

	printf("cmd: %s\n", cmd);
	pid = fork();
	if (pid != 0)
	{
		printf("Executing\n");
		execve(cmd, av, envp);
	}
	else
	{
		printf("Waitign for execution ...\n");
		sleep(1);
		wait(0);
	}
	return (0);
}