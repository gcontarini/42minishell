/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:21:53 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/29 12:21:58 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_ls_path_dir(void);

char	*find_bin_path(const char *cmd)
{
	char	**ls_path_dir;
	char	*dir;
	char	*cmd_path;
	int		pos;

	pos = 0;
	cmd_path = NULL;
	ls_path_dir = find_ls_path_dir();
	if (!ls_path_dir)
		return (cmd_path);
	while (ls_path_dir[pos])
	{
		dir = ft_strjoin(ls_path_dir[pos], "/");
		if (dir == NULL)
			break ;
		cmd_path = ft_strjoin(dir, cmd);
		free(dir);
		if (cmd_path == NULL || access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		pos++;
	}
	free_split(ls_path_dir);
	return (cmd_path);
}

static char	**find_ls_path_dir(void)
{
	char	**ls_path_dir;
	char	*path_var;

	path_var = getenv("PATH");
	if (!path_var)
		return (NULL);
	ls_path_dir = ft_split(path_var, ':');
	if (!ls_path_dir)
		ls_path_dir = NULL;
	return (ls_path_dir);
}
