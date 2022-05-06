/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:21:53 by nprimo            #+#    #+#             */
/*   Updated: 2022/05/06 10:48:18 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_ls_path_dir(void);
static char	*expand_cmd(const char *cmd);

char	*find_bin_path(const char *cmd)
{
	char	**ls_path_dir;
	char	*dir;
	char	*cmd_path;
	int		pos;

	pos = 0;
	cmd_path = NULL;
	if (access(cmd, F_OK & X_OK) == 0)
	{
		cmd_path = expand_cmd(cmd);
		return (cmd_path);
	}
	ls_path_dir = error_check_pointer(find_ls_path_dir());
	while (ls_path_dir[pos])
	{
		dir = error_check_pointer(ft_strjoin(ls_path_dir[pos], "/"));
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
	ls_path_dir = error_check_pointer(ft_split(path_var, ':'));
	return (ls_path_dir);
}

static char *expand_cmd(const char *cmd)
{
	char *cmd_path;

	cmd_path = error_check_pointer(ft_strdup(cmd));
	// or expand ../ or ./ if needed;
	return (cmd_path);
}
