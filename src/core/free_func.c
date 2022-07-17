/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:19:39 by nprimo            #+#    #+#             */
/*   Updated: 2022/07/17 20:03:34 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(void *av_void)
{
	int		pos;
	char	**av;

	av = (char **) av_void;
	pos = 0;
	while (av && av[pos])
	{
		if (av[pos])
			free(av[pos]);
		pos++;
	}
	free(av);
}

void	free_cmd(void *cmd_void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) cmd_void;
	if (cmd)
	{
		if (cmd->av)
			free_split(cmd->av);
		if (cmd->fd_pair_list)
			ft_lstclear(&cmd->fd_pair_list, free_dict);
		free(cmd);
	}
}

void	free_fd(void *fd_void)
{
	t_fd	*fd;

	fd = (t_fd *) fd_void;
	if (fd)
	{
		if (fd->fname)
			free(fd->fname);
		if (fd->redirection)
			free(fd->redirection);
	}
}

void	free_dict(void *var_void)
{
	t_dict	*var;

	var = (t_dict *) var_void;
	if (var)
	{
		if (var->key)
			free(var->key);
		if (var->value)
			free(var->value);
		free(var);
	}
}

void	free_shell(t_shell sh)
{
	if (sh.env)
		ft_lstclear(&sh.env, free_dict);
	if (sh.input)
		free(sh.input);
	if (sh.token_list)
		ft_lstclear(&sh.token_list, free_token);
	if (sh.cmd_list)
		ft_lstclear(&sh.cmd_list, free_cmd);
}

void	free_exp(void *exp_void)
{
	t_exp	*exp;

	exp = (t_exp *) exp_void;
	if (exp)
	{
		if (exp->table)
			free(exp->table);
		if (exp->var_names)
			free_split(exp->var_names);
	}
}

void	free_token(void *token_void)
{
	t_token	*token;

	token = (t_token *) token_void;
	if (token)
	{
		if (token->s)
			free(token->s);
		free(token);
	}
}

void	free_t(void *token_void)
{
	t_token	*token;

	token = (t_token *) token_void;
	if (token)
		free(token);
}
