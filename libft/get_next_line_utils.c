/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:08:41 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/25 16:24:49 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_has_newline(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

int	ft_buffer_is_empty(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] == 0 && i < BUFFER_SIZE)
		i++;
	if (i == BUFFER_SIZE)
		return (1);
	return (0);
}

char	*ft_check_str(char *str, int charead)
{
	if (ft_strlen(str) && charead != -1)
		return (str);
	free(str);
	return (0);
}

char	*ft_buffer_to_str(char *src, int charead)
{
	int		count;
	char	*nstr;

	count = 0;
	while (src[count] != '\n' && count < charead)
		count++;
	if (src[count] == '\n')
		count++;
	nstr = malloc(count + 1);
	if (!nstr)
		return (0);
	count = 0;
	while (src[count] != '\n' && count < charead)
	{
		nstr[count] = src[count];
		count++;
	}
	if (src[count] == '\n')
		nstr[count++] = '\n';
	nstr[count] = '\0';
	return (nstr);
}
