/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:24:17 by gcontari          #+#    #+#             */
/*   Updated: 2022/06/24 15:41:14 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_expander
{
	t_uint	counter;
	char	**var_names;
	bool	*table;
}	t_exp;

static char		**split_env_names(const char *input, t_exp exp, t_shell sh);
static void		cpy_and_exp(char *dst, const char *src, t_exp exp);
static void		create_exp_table(const char *input, t_exp exp);
static t_uint	expansionlen(const char *input, t_exp exp);

char	*expander(t_shell sh, const char *input)
{
	t_exp	exp;
	char	*output;

	exp.counter = str_count_char(input, '$');
	exp.table = xmalloc(exp.counter, NULL, sh);
	create_exp_table(input, exp);
	exp.var_names = xmalloc((exp.counter + 1) * sizeof(char *), &exp, sh);
	split_env_names(input, exp, sh);
	output = xmalloc(expansionlen(input, exp) + 1, &exp, sh);
	cpy_and_exp(output, input, exp);
	free(exp.table);
	free_arr(exp.var_names);
	return (output);
}

static char	**split_env_names(const char *input, t_exp exp, t_shell sh)
{
	char	**tmp;
	char	*ptr;

	tmp = exp.var_names;
	*tmp = NULL;
	while (input && *input)
	{
		input = ft_strchr(input, '$');
		if (!input || *input != '$')
			continue ;
		ptr = (char *)++input;
		while (*ptr && !ft_strchr(EXP_SET, *ptr))
			ptr++;
		*tmp = xmalloc(ptr - input + 1, &exp, sh);
		ft_strlcpy(*tmp++, input, ptr - input + 1);
		*tmp = NULL;
	}
	return (exp.var_names);
}

static void	cpy_and_exp(char *dst, const char *src, t_exp exp)
{
	char	*p;
	char	**vars;
	bool	*exp_tab;

	vars = exp.var_names;
	exp_tab = exp.table;
	while (src && *src)
	{
		if (*src == '$' && *exp_tab)
		{
			src += ft_strlen(*vars) + 1;
			p = getenv(*vars++);
			while (p && *p)
				*dst++ = *p++;
			exp_tab++;
			continue ;
		}
		else if (*src == '$' && !*exp_tab++)
			vars++;
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

static t_uint	expansionlen(const char *input, t_exp exp)
{
	t_uint	size;
	bool	*exp_tab;
	char	**vars;

	exp_tab = exp.table;
	vars = exp.var_names;
	size = 0;
	while (*input)
	{
		if (*input++ != '$' || !*exp_tab++)
		{
			size++;
			continue ;
		}
		input += ft_strlen(*vars);
		size += ft_strlen(getenv(*vars++));
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
