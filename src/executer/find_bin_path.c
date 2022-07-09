/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:21:53 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/08 11:56:57 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_ls_path_dir(t_list *env, t_shell sh);

char	*find_bin_path(const char *bin, t_list *env, t_shell sh)
{
	char	**ls_path_dir;
	char	*bin_path;
	size_t	tot_len;
	int		pos;

	pos = 0;
	bin_path = NULL;
	ls_path_dir = find_ls_path_dir(env, sh);
	while (ls_path_dir && ls_path_dir[pos])
	{
		tot_len = ft_strlen(ls_path_dir[pos]) + ft_strlen(bin) + 2;
		bin_path = xmc(malloc(sizeof(char) * tot_len), NULL, 0, sh);
		ft_strlcpy(bin_path, ls_path_dir[pos], ft_strlen(ls_path_dir[pos]) + 1);
		ft_strlcat(bin_path, "/", ft_strlen(bin_path) + 2);
		ft_strlcat(bin_path, bin, ft_strlen(bin_path) + ft_strlen(bin) + 1);
		if (access(bin_path, X_OK) == 0)
			break ;
		free(bin_path);
		pos++;
	}
	if (ls_path_dir && ls_path_dir[pos] == NULL)
		bin_path = xmc(ft_strndup(bin, ft_strlen(bin)), NULL, 0, sh);
	free_split(ls_path_dir);
	return (bin_path);
}

static char	**find_ls_path_dir(t_list *env, t_shell sh)
{
	char	**ls_path_dir;
	char	*path_var;

	path_var = ft_getenv("PATH", env);
	if (!path_var)
		return (NULL);
	ls_path_dir = xmc(ft_split(path_var, ':'), NULL, 0, sh);
	return (ls_path_dir);
}
