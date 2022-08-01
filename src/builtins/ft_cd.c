/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 21:45:53 by nprimo            #+#    #+#             */
/*   Updated: 2022/08/01 20:03:44 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env_var(t_dict *var, char *new_val, void (*del) (void *));
int			get_ac(char **av);

int	ft_cd(t_cmd *cmd, t_shell *sh)
{
	char	*oldpwd;
	char	*cwd;
	t_dict	*var;

	cwd = NULL;
	if (get_ac(cmd->av) == 1 && chdir(sh->homepath) != -1)
		;
	else if (chdir(cmd->av[1]) == -1 || get_ac(cmd->av) > 2
		|| get_ac(cmd->av) > 2)
		return (1);
	oldpwd = ft_getenv("PWD", sh->env);
	var = get_dict_var("OLDPWD", sh->env);
	if (var)
		update_env_var(var, oldpwd, free);
	var = get_dict_var("PWD", sh->env);
	if (var)
		update_env_var(var, getcwd(cwd, 0), NULL);
	return (0);
}

static int	update_env_var(t_dict *var, char *new_val, void (*del) (void *))
{
	char	*tmp;

	tmp = var->value;
	var->value = new_val;
	if (tmp != NULL && del)
		del(tmp);
	return (0);
}
