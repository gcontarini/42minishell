/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:53:26 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/20 17:12:10 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_ac(char **av);
static void	display_env(t_list *env, int fd);

int	ft_export(t_cmd *cmd, t_shell sh)
{
	if (get_ac(cmd->av) == 1)
		display_env(sh.env, cmd->out.fd);
	return (0);
}

static int	get_ac(char **av)
{
	int pos;

	pos = 0;
	while (av[pos])
		pos++;
	return (pos);
}

static void	display_env(t_list *env, int fd)
{
	t_dict	*var;

	while (env)
	{
		var = (t_dict *) env->content;
		write(fd, "declare -x ", ft_strlen("declare -x "));
		write(fd, var->key, ft_strlen(var->key));
		if (var->value)
		{
			write(fd, "=\"", 2);
			write(fd, var->value, ft_strlen(var->value));
			write(fd, "\"", 1);
		}
		write(fd, "\n", 1);
		env = env->next;
	}
}