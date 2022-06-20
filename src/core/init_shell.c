/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:05:16 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/20 12:13:31 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_dict	*str_to_dict(char *str);
static t_list	*envp_to_dict_list(char **envp);
static void		unset_oldpwd(t_list **env);
static void		update_shlvl(t_list *env);

t_shell	init_shell(char **envp)
{
	t_shell	sh;

	sh.env = envp_to_dict_list(envp);
	update_shlvl(sh.env);
	unset_oldpwd(&sh.env);
	sh.input = NULL;
	sh.token_list = NULL;
	sh.cmd_list = NULL;
	return (sh);
}

static t_dict	*str_to_dict(char *str)
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

static t_list	*envp_to_dict_list(char **envp)
{
	int		pos;
	t_list	*env;
	t_dict	*var;

	env = NULL;
	pos = 0;
	while (envp[pos])
	{
		var = str_to_dict(envp[pos]);
		ft_lstadd_back(&env, ft_lstnew(var));
		pos++;
	}
	return (env);
}

static void	update_shlvl(t_list *env)
{
	t_dict	*var;
	int		sh_lvl;
	char	*tmp;

	while (env)
	{
		var = (t_dict *) env->content;
		if (ft_strncmp(var->key, "SHLVL", ft_strlen("SHLVL")) == 0)
		{
			sh_lvl = ft_atoi(var->value) + 1;
			tmp = var->value;
			var->value = error_check_pointer(ft_itoa(sh_lvl));
			free(tmp);
			return ;
		}
		env = env->next;
	}
}

static void	unset_oldpwd(t_list **env)
{
	t_list	*oldpwd;
	t_list	*head;
	t_dict	*var;

	oldpwd = NULL;
	head = *env;
	while (head)
	{
		var = (t_dict *) head->content;
		if (ft_strncmp(var->key, "OLDPWD", ft_strlen("OLDPWD")) == 0)
		{
			oldpwd = head;
			break ;
		}
		head = head->next;
	}
	if (oldpwd)
		ft_lstdelone(ft_lst_remove(env, oldpwd->content), free_dict);
}
