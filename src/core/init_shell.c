/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:05:16 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/18 15:09:33 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*envp_to_dict(char **envp);

t_shell	init_shell(char **envp)
{
	t_shell	sh;

	sh.env = envp_to_dict(envp);
	sh.input = NULL;
	sh.token_list = NULL;
	sh.cmd_list = NULL;
	return (sh);
}

static t_dict	*parse_var(char *str)
{
	t_dict	*var;
	size_t	len_key;
	char	*value;

	var = error_check_pointer(malloc(sizeof(t_dict) * 1));
	value = ft_strchr(str, '=') + 1;
	var->value = error_check_pointer(ft_strndup(value, ft_strlen(value)));
	len_key = ft_strlen(str) - ft_strlen(value) - 1;
	var->key = error_check_pointer(ft_strndup(str, len_key));
	return (var);
}

static t_list	*envp_to_dict(char **envp)
{
	int		pos;
	t_list	*env;
	t_dict	*var;

	env = NULL;
	pos = 0;
	while (envp[pos])
	{
		var = parse_var(envp[pos]);
		ft_lstadd_back(&env, ft_lstnew(var));
		pos++;
	}
	return (env);
}
