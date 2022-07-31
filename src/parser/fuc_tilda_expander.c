/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuc_tilda_expander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:24:17 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/31 16:11:41 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		_cpy_home(char *dst, const char *src, t_exp exp, t_shell *sh);
static void		_create_tilda_exp_table(const char *input, t_exp exp);
static t_uint	_tilda_explen(const char *input, t_exp exp, t_shell *sh);

char	*f_tilda_expander(t_shell *sh, const char *input)
{
	t_exp	exp;
	char	*output;

	exp.counter = str_count_char(input, '~');
	if (exp.counter == 0)
		return (NULL);
	exp.vars = NULL;
	exp.table = xmc(malloc(exp.counter), NULL, T_CMD, sh);
	_create_tilda_exp_table(input, exp);
	output = xmc(malloc(_tilda_explen(input, exp, sh) + 1), &exp, T_EXP, sh);
	_cpy_home(output, input, exp, sh);
	free_exp(&exp);
	return (output);
}

static void	_cpy_home(char *dst, const char *src, t_exp exp, t_shell *sh)
{
	char	*p;

	while (src && *src)
	{
		if (*src == '~' && *exp.table)
		{
			src++;
			p = ft_getenv("HOME", sh->env);
			while (p && *p)
				*dst++ = *p++;
			exp.table++;
			continue ;
		}
		*dst++ = *src++;
	}
	*dst = 0;
	return ;
}

static void	_create_tilda_exp_table(const char *input, t_exp exp)
{
	bool	quote[2];
	bool	enabled;

	quote[0] = false;
	quote[1] = false;
	enabled = true;
	while (exp.counter != 0)
	{
		if (*input == '\'' && !quote[1])
			quote[0] = !quote[0];
		else if (*input == '\"' && !quote[0])
			quote[1] = !quote[1];
		else if (*input == '~')
		{
			if ((!quote[0] || !ft_strchr(input, '\''))
				|| !quote[1] || !ft_strchr(input, '\"'))
				*exp.table++ = (ft_strchr(" /", *(input + 1)) && enabled);
			else
				*exp.table++ = false;
			exp.counter--;
		}
		enabled = (*input++ == ' ');
	}
	return ;
}

static t_uint	_tilda_explen(const char *input, t_exp exp, t_shell *sh)
{
	t_uint	size;
	bool	*exp_tab;

	exp_tab = exp.table;
	size = 0;
	while (*input)
	{
		if (*input++ != '~' || !*exp_tab++)
		{
			size++;
			continue ;
		}
		size += ft_strlen(ft_getenv("HOME", sh->env));
	}
	return (size);
}
