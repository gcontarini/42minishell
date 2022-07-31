/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:45:11 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/31 18:46:13 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(void *cmd_void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) cmd_void;
	if (cmd->av)
		free_split(cmd->av);
	free_fd(&cmd->in);
	free_fd(&cmd->out);
	free(cmd);
}

void	free_fd(void *fd_void)
{
	t_fd	*fd;

	fd = (t_fd *) fd_void;
	if (fd)
	{
		if (fd->fname)
			free(fd->fname);
		if (fd->red)
			free(fd->red);
	}
}

void	free_dict(void *var_void)
{
	t_dict	*var;

	var = (t_dict *) var_void;
	if (var)
	{
		if (var->key != NULL)
			free(var->key);
		if (var->value != NULL)
			free(var->value);
		free(var);
	}
}

void	free_shell(t_shell *sh)
{
	if (sh->env)
		ft_lstclear(&sh->env, free_dict);
	if (sh->input)
		free(sh->input);
	if (sh->token_list)
		ft_lstclear(&sh->token_list, free_token);
	if (sh->cmd_list)
		ft_lstclear(&sh->cmd_list, free_cmd);
}

void	free_exp(void *exp_void)
{
	t_exp	*exp;

	exp = (t_exp *) exp_void;
	if (exp)
	{
		if (exp->table)
			free(exp->table);
		if (exp->vars)
			free_split(exp->vars);
	}
}
