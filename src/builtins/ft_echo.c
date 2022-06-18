/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:21:43 by nprimo            #+#    #+#             */
/*   Updated: 2022/06/18 16:29:55 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_concat(char **string_list, char *sep);

int	ft_echo(t_cmd *cmd)
{
	char	*output;
	char	*tmp;
	int		n_flag;
	int		pos;

	n_flag = 0;
	pos = 1;
	if (ft_strncmp(cmd->av[1], "-n", 3) == 0)
	{
		n_flag = 1;
		pos += 1;
	}
	output = ft_concat(&(cmd->av[pos]), " ");
	if (n_flag == 0)
	{
		tmp = output;
		output = error_check_pointer(ft_strjoin(output, "\n"));
		free(tmp);
	}
	write(cmd->out.fd, output, ft_strlen(output));
	return (0);
}

static char	*ft_concat(char **string_list, char *sep)
{
	char	*output;
	char	*tmp;
	int		pos;

	output = error_check_pointer(malloc(sizeof(char) * 1));
	output[0] = '\0';
	pos = 0;
	while (string_list[pos])
	{
		tmp = output;
		output = error_check_pointer(ft_strjoin(output, string_list[pos]));
		free(tmp);
		pos++;
		if (string_list[pos])
		{
			tmp = output;
			output = error_check_pointer(ft_strjoin(output, sep));
		}
	}
	return (output);
}
