/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:24:52 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/18 17:25:13 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect(int fd_in, int fd_out);
char		**dict_list_to_av(t_list *dict_list);

int	exec_cmd(t_cmd cmd, t_shell sh)
{
	pid_t	pid;
	char	*bin_path;

	bin_path = find_bin_path(cmd.av[0]);
	if (!bin_path)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		error_check(redirect(cmd.in.fd, cmd.out.fd));
		error_check(execve(bin_path, cmd.av, dict_list_to_av(sh.env)));
	}
	if (cmd.in.fd != STDIN_FILENO)
		close(cmd.in.fd);
	if (cmd.out.fd != STDOUT_FILENO)
		close(cmd.out.fd);
	free(bin_path);
	return (0);
}

static int	redirect(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1
			|| close(fd_in) == -1)
			return (-1);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1
			|| close(fd_out) == -1)
			return (-1);
	}
	return (0);
}

char	*dict_to_str(t_dict *var)
{
	char	*str;
	size_t	tot_len;

	tot_len = ft_strlen(var->key) + ft_strlen(var->value) + 2;
	str = error_check_pointer(malloc(sizeof(char) * tot_len));
	ft_strlcpy(str, var->key, ft_strlen(var->key) + 1);
	ft_strlcat(str, "=", ft_strlen(str) + 2);
	ft_strlcat(str, var->value, ft_strlen(str) + ft_strlen(var->value) + 1);
	return (str);
}

char	**dict_list_to_av(t_list *dict_list)
{
	char	**array_string;
	int		lst_size;
	int		pos;

	lst_size = ft_lstsize(dict_list);
	array_string = error_check_pointer(malloc(sizeof(char *)
				* (lst_size + 1)));
	pos = 0;
	while (dict_list && pos < lst_size)
	{
		array_string[pos] = dict_to_str((t_dict *) dict_list->content);
		dict_list = dict_list->next;
		pos++;
	}
	array_string[pos] = NULL;
	return (array_string);
}
