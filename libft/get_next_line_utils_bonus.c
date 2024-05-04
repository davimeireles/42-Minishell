/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:40:33 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/22 12:40:36 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_eol(char *getting)
{
	if (!getting)
		return (0);
	while (*getting)
	{
		if (*getting == '\n')
			return (1);
		getting++;
	}
	return (0);
}

size_t	ft_linelen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin_nl(char *getting, char *aux)
{
	size_t	len;
	char	*joined;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = ft_strlen(getting) + ft_strlen(aux);
	joined = malloc(len + 1);
	if (!joined)
		return (NULL);
	while (getting && getting[i])
	{
		joined[i] = getting[i];
		i++;
	}
	while (aux && aux[j])
		joined[i++] = aux[j++];
	joined[i] = '\0';
	if (getting)
		free (getting);
	return (joined);
}

char	*ft_strncpy(char *dest, char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
