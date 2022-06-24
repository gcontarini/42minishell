/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:21:53 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/24 13:53:03 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_ls_path_dir(t_list *env);

char	*find_bin_path(const char *bin, t_list *env)
{
	char	**ls_path_dir;
	char	*dir;
	char	*bin_path;
	int		pos;

	pos = 0;
	bin_path = NULL;
	if (access(bin, F_OK & X_OK) == 0)
		return (error_check_pointer(ft_strndup(bin, ft_strlen(bin))));
	ls_path_dir = error_check_pointer(find_ls_path_dir(env));
	while (ls_path_dir[pos])
	{
		dir = error_check_pointer(ft_strjoin(ls_path_dir[pos], "/"));
		bin_path = ft_strjoin(dir, bin);
		free(dir);
		if (bin_path == NULL || access(bin_path, X_OK) == 0)
			break ;
		pos++;
	}
	free_split(ls_path_dir);
	return (bin_path);
}

static char	**find_ls_path_dir(t_list *env)
{
	char	**ls_path_dir;
	char	*path_var;

	path_var = ft_getenv("PATH", env);
	if (!path_var)
		return (NULL);
	ls_path_dir = error_check_pointer(ft_split(path_var, ':'));
	return (ls_path_dir);
}
