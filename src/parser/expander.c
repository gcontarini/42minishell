/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:24:17 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/26 14:50:20 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**split_env_names(const char *input, t_exp exp, t_shell sh);
static void		cpy_and_exp(char *dst, const char *src, t_exp exp, t_shell sh);
static void		create_exp_table(const char *input, t_exp exp);
static t_uint	expansionlen(const char *input, t_exp exp, t_shell sh);

char	*expander(t_shell sh, const char *input)
{
	t_exp	exp;
	char	*output;

	exp.counter = str_count_char(input, '$');
	exp.table = xmc(malloc(exp.counter), NULL, T_CMD, sh);
	create_exp_table(input, exp);
	exp.vars = xmc(
			malloc((exp.counter + 1) * sizeof(char *)), &exp, T_EXP, sh);
	split_env_names(input, exp, sh);
	printf("EXP LEN: %d\n", expansionlen(input, exp, sh));
	output = xmc(malloc(expansionlen(input, exp, sh) + 1), &exp, T_EXP, sh);
	cpy_and_exp(output, input, exp, sh);
	free_exp(&exp);
	return (output);
}

static char	**split_env_names(const char *input, t_exp exp, t_shell sh)
{
	char	**tmp;
	char	*ptr;

	tmp = exp.vars;
	*tmp = NULL;
	while (input && *input)
	{
		input = ft_strchr(input, '$');
		if (!input || *input != '$')
			continue ;
		ptr = (char *)++input;
		while (*ptr && !ft_strchr(EXP_SET, *ptr))
			ptr++;
		*tmp = xmc(malloc(ptr - input + 1), &exp, T_EXP, sh);
		ft_strlcpy(*tmp++, input, ptr - input + 1);
		*tmp = NULL;
	}
	return (exp.vars);
}

static void	cpy_and_exp(char *dst, const char *src, t_exp exp, t_shell sh)
{
	char	*p;

	while (src && *src)
	{
		printf("OUT %c\n", *src);
		if (*src == '$' && *exp.table)
		{
			src += (*exp.vars && **exp.vars != '?') * ft_strlen(*exp.vars)
				+ (*exp.vars && **exp.vars == '?') + 1;
			printf("IN %c\n", *src);
			if (*exp.vars && **exp.vars == '?')
				p = xmc(ft_itoa(sh.exit_status), &exp, T_EXP, sh);
			else
				p = ft_getenv(*exp.vars, sh.env);
			while (p && *p)
				*dst++ = *p++;
			if (*exp.vars && **exp.vars == '?')
				free(p - ft_intlen(sh.exit_status));
			exp.table++;
			exp.vars++;
			continue ;
		}
		exp.vars = exp.vars + (1 * (*src == '$' && !*exp.table++));
		*dst++ = *src++;
	}
	*dst = 0;
	return ;
}

static void	create_exp_table(const char *input, t_exp exp)
{
	bool	quote[2];
	bool	*exp_ptr;
	t_uint	count;

	exp_ptr = exp.table;
	count = exp.counter;
	quote[0] = false;
	quote[1] = false;
	while (count != 0)
	{
		if (*input == '\'' && !quote[1])
			quote[0] = !quote[0];
		else if (*input == '\"' && !quote[0])
			quote[1] = !quote[1];
		else if (*input == '$')
		{
			if (!quote[0] || !ft_strchr(input, '\''))
				*exp_ptr++ = true;
			else
				*exp_ptr++ = false;
			count--;
		}
		input++;
	}
	return ;
}

static t_uint	expansionlen(const char *input, t_exp exp, t_shell sh)
{
	t_uint	size;
	bool	*exp_tab;
	char	**vars;

	exp_tab = exp.table;
	vars = exp.vars;
	size = 0;
	while (*input)
	{
		if (*input++ != '$' || !*exp_tab++)
		{
			size++;
			continue ;
		}
		if (*vars && **vars == '?')
			size += ft_intlen(sh.exit_status);
		else
			size += ft_strlen(ft_getenv(*vars, sh.env));
		printf("%s\n", *vars);
		input += ft_strlen(*vars++);
	}
	return (size);
}

// int	main(void) {
// 	char	*p;
// 	t_shell	sh;

// 	p = expander(sh, "echo \"Hello\"");
// 	printf("%s\n", p);
// 	free(p);
// 	p = expander(sh, "echo $PWD");
// 	printf("%s\n", p);
// 	free(p);
// 	p = expander(sh, "echo \"$PWD\"");
// 	printf("%s\n", p);
// 	free(p);
// 	p = expander(sh, "echo '$PWD'");
// 	printf("%s\n", p);
// 	free(p);
// 	p = expander(sh, "cd $PWD | echo $SHELL");
// 	printf("%s\n", p);
// 	free(p);
// 	p = expander(sh, "cd $PWD | echo $SHELL > zip $HOME");
// 	printf("%s\n", p);
// 	free(p);
// 	p = expander(sh, "cd $PWD| echo $SHELL > zip $HOME");
// 	printf("%s\n", p);
// 	free(p);
// 	p = expander(sh, "cd \"$PWD lets go\" | echo $SHELL > zip $HOME");
// 	printf("%s\n", p);
// 	free(p);
// 	p = expander(sh, "cd '$PWD lets go' | echo $SHELL > zip $HOME");
// 	printf("%s\n", p);
// 	free(p);
// 	p = expander(sh, "cd \"$PWD let's go\" | echo $SHELL > zip $HOME");
// 	printf("%s\n", p);
// 	free(p);
// 	p = expander(sh, "cd \"'$PWD' let's go\" | echo $SHELL > zip $HOME");
// 	printf("%s\n", p);
// 	free(p);
// 	p = expander(sh, "cd '\"$PWD\" lets go' | echo $SHELL > zip $HOME");
// 	printf("%s\n", p);
// 	free(p);
// 	return (0);
// }
