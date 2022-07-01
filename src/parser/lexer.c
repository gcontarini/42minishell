/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:13:27 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/01 17:18:17 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*quote_handler(const char *inpt, t_shell *sh);
static const char	*dir_handler(const char *inpt, t_shell *sh);
static const char	*normal_handler(const char *inpt, t_shell *sh);
static t_list		*create_token(const char *str,
						t_uint n, t_ttype token_type, t_shell *sh);

t_list	*lexer(t_shell sh, const char *inpt)
{
	t_token	*token;

	while (inpt && *inpt)
	{
		while (*inpt && ft_strchr(SPACE_SET, *inpt))
			inpt++;
		if (*inpt && ft_strchr("\"\'", *inpt))
			inpt = quote_handler(inpt, &sh);
		else if (*inpt && ft_strchr(METACHAR_SET, *inpt))
			inpt = dir_handler(inpt, &sh);
		else if (*inpt)
			inpt = normal_handler(inpt, &sh);
	}
	return (sh.token_list);
}

const char	*quote_handler(const char *inpt, t_shell *sh)
{
	char		*p;

	p = ft_strchr(inpt + 1, *inpt);
	if (!p)
		return (normal_handler(inpt, sh));
	sh->token_list = create_token(inpt + 1, p - inpt - 1, QUOTE, sh);
	return (p + 1);
}

const char	*dir_handler(const char *inpt, t_shell *sh)
{
	char		*p;
	t_uint		step;

	step = 1;
	if (*(inpt + 1) == *inpt)
		step++;
	sh->token_list = create_token(inpt, step, REDIR, sh);
	return (inpt + step);
}

const char	*normal_handler(const char *inpt, t_shell *sh)
{
	char		*p;

	p = inpt;
	while (*p && !ft_strchr(EXP_SET, *p))
		p++;
	sh->token_list = create_token(inpt, p - inpt, TOKEN, sh);
	return (p);
}

static t_list	*create_token(const char *str, t_uint n, t_ttype token_type, t_shell *sh)
{
	char		*token_str;
	t_list		*node;
	t_token		*token;

	token_str = xmc(ft_strndup(str, n), NULL, 0, *sh);
	token = xmc(malloc(sizeof(t_token)), token_str, T_MEM, *sh);
	token->s = token_str;
	token->t = token_type;
	node = xmc(ft_lstnew(token), token, T_TOKEN, *sh);
	ft_lstadd_back(&(sh->token_list), node);
	return (sh->token_list);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_shell sh;
// 	char	*test_cases[] = {
// 		"echo adsad > 1412341",
// 		"\"echo adsad\" > 1412341",
// 		"\"echo ad\'sad > 14\"12341",
// 		"\"\"echo adsad > 1412341",
// 		"\'echo adsad >\' 1412341",
// 		"ad|ad > 1412341",
// 		"echo <<adsad >> 1412341",
// 		"\t\t\n     echo hi | \t\t\t ola",
// 		"echo asdf\"asd\"asd",
// 		0
// 	};

// 	sh = init_shell(envp);
// 	for (int i = 0; test_cases[i] != NULL; i++) {
// 		for (t_list *curr = lexer(sh, test_cases[i]); curr; curr = curr->next)
// 			printf("%s - %d\n", ((t_token *) curr->content)->s, ((t_token *) curr->content)->t);
// 		printf("----------------\n");
// 	}
// 	free_shell(sh);
// 	return (0);
// }
