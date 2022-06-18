/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:19:39 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/18 12:25:27 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_fd(t_fd *fd);

void	free_split(char **av)
{
	int	pos;

	pos = 0;
	while (av && av[pos])
	{
		free(av[pos]);
		pos++;
	}
	free(av);
}

void	free_cmd(void *cmd_void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) cmd_void;
	ft_lstclear(&cmd->token_list, NULL);
	if (cmd->av)
		free_split(cmd->av);
	free_fd(&cmd->in);
	free_fd(&cmd->out);
}

static void	free_fd(t_fd *fd)
{
	if (fd)
	{
		if (fd->fname)
			free(fd->fname);
		if (fd->redirection)
			free(fd->redirection);
	}
}

void	free_dict(void *var_void)
{
	t_dict	*var;

	var = (t_dict *) var_void;
	if (var)
	{
		if (var->key)
			free(var->key);
		if (var->value)
			free(var->value);
		free(var);
	}
}
