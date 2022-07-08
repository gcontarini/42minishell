/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:16:55 by gcontari          #+#    #+#             */
/*   Updated: 2022/07/08 20:47:09 by gcontari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parser(t_shell *sh, const char *inpt)
{
	char	*inpt_exp;

	inpt_exp = expander(*sh, inpt);
	free((char *) inpt);
	sh->input = inpt_exp;
	sh->token_list = lexer(*sh, inpt_exp);
	sh->token_list = build_syntax_tree(sh);
	return (sh->token_list);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_shell	sh;
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
// 		"echo aaaaaaa\"bbbbbbbbbb\"cccccccc dddddddd",
// 		"echo aaaaaaa \"bbbbbbbbbb\"cccccccc dddddddd",
// 		"echo aaaaaaa \" bbbbbbbbbb\"cccccccc dddddddd",
// 		"echo aaaaaaa \" bbbbbbbbbb\"cccccccc dddddddd",
// 		"echo aaaaaaa>>bbbbbbbb",
// 		"echo aaaaaaa>>\"cccccccccc\">>bbbbbbbb",
// 		"echo aaaaaaa>> >>bbbbbbbb",
// 		0
// 	};

// 	for (int i = 0; test_cases[i] != NULL; i++) {
// 		sh = init_shell(envp);
// 		printf("------- TEST NUMBER %d ---------\n", i);
// 		for (t_list *curr = parser(&sh, test_cases[i]); curr; curr = curr->next)
// 		{
// 			printf("%s - %d\n", ((t_token *) curr->content)->s,
// 				((t_token *) curr->content)->t);
// 		}
// 		printf("----------------\n");
// 		free_shell(sh);
// 	}
// 	return (0);
// }
