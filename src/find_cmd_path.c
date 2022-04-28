/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:08:44 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/28 16:25:18 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	**find_ls_path_dir(char **envp);

char	*find_cmd_path(const char *cmd, char **envp)
{
	char	**ls_path_dir;
	char	*dir;
	char	*cmd_path;
	int		pos;

	pos = 0;
	cmd_path = NULL;
	ls_path_dir = find_ls_path_dir(envp);
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

static char	**find_ls_path_dir(char **envp)
{
	char	**ls_path_dir;
	int		pos;

	pos = 0;
	ls_path_dir = NULL;
	while (envp[pos])
	{
		if (ft_strncmp(envp[pos], "PATH", 4) == 0)
		{
			ls_path_dir = ft_split(&envp[pos][ft_strlen("PATH=")], ':');
			if (!ls_path_dir)
				ls_path_dir = NULL;
			break ;
		}
		pos++;
	}
	return (ls_path_dir);
}
