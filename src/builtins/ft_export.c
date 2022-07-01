/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:53:26 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/01 10:05:11 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_ac(char **av);
static void	display_env(t_list *env, int fd);
static int	add_to_env(char *key_value, t_shell sh);

int	ft_export(t_cmd *cmd, t_shell sh)
{
	int	pos;

	if (get_ac(cmd->av) == 1)
		display_env(sh.env, cmd->out.fd);
	else
	{
		pos = 1;
		while (cmd->av[pos])
		{
			add_to_env(cmd->av[pos], sh);
			pos++;
		}
	}
	return (0);
}

static int	get_ac(char **av)
{
	int	pos;

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

static int	add_to_env(char *key_value, t_shell sh)
{
	t_dict	*var;
	t_dict	*new_var;
	t_list	*new_el;
	char	*tmp;

	new_var = str_to_dict(key_value, sh);
	if (get_dict_var(new_var->key, sh.env))
	{
		var = get_dict_var(new_var->key, sh.env);
		if (new_var->value)
		{
			tmp = var->value;
			var->value = new_var->value;
			free(tmp);
		}
	}
	else
	{
		new_el = xmc(ft_lstnew(new_var), NULL, 0, sh);
		ft_lstadd_back(&sh.env, new_el);
	}
	return (0);
}
