/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 21:45:53 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/24 22:02:25 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env_var(t_dict *var, char *new_val);

int	ft_cd(t_cmd *cmd, t_shell sh)
{
	char	*oldpwd;
	char	*cwd;
	t_dict	*var;

	cwd = NULL;
	if (chdir(cmd->av[1]) == -1)
		return (1);
	oldpwd = ft_getenv("PWD", sh.env);
	var = get_dict_var("OLDPWD", sh.env);
	if (var)
		update_env_var(var, oldpwd);
	var = get_dict_var("PWD", sh.env);
	if (var)
		update_env_var(var, getcwd(cwd, 0));
	return (0);
}

static int	update_env_var(t_dict *var, char *new_val)
{
	char	*tmp;

	tmp = var->value;
	var->value = new_val;
	free(tmp);
	return (0);
}
