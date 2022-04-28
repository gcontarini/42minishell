/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:17:58 by nprimo            #+#    #+#             */
/*   Updated: 2022/04/28 12:15:24 by nprimo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, int n)
{
	size_t	len;
	size_t	pos;
	char	*dest;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if ((int) len > n)
		len = n;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	pos = 0;
	while (str[pos] && pos < len)
	{
		dest[pos] = str[pos];
		pos++;
	}
	dest[pos] = '\0';
	return (dest);
}
