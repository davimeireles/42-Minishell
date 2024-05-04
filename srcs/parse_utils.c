/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:19:22 by dmeirele          #+#    #+#             */
/*   Updated: 2024/04/22 15:51:06 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pad(char *src, char *dest, int i, int j)
{
	char	skip;

	while (src[i])
	{
		if (src[i] && find_char(src[i], "|><") && !quotes_open(src, i))
		{
			dest[j++] = ' ';
			skip = src[i];
			while (src[i] == skip)
				dest[j++] = src[i++];
			dest[j++] = ' ';
			continue ;
		}
		dest[j++] = src[i];
		i++;
	}
}

char	*pad_central(char *line)
{
	int		extra;
	char	*ret;

	extra = padding_needed(line, 0, 0);
	if (extra == 0)
		return (ft_strdup(line));
	ret = (char *)ft_calloc(1, ft_strlen(line) + extra + 1);
	pad(line, ret, 0, 0);
	return (ret);
}

int	padding_needed(char *line, int i, int pad)
{
	char	skip;

	while (line[i])
	{
		if (line[i] && find_char(line[i], "|><") && !quotes_open(line, i))
		{
			skip = line[i];
			while (line[i] && line[i] == skip)
				i++;
			pad += 2;
			continue ;
		}
		i++;
	}
	return (pad);
}

int	pipe_check(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '|' && !quotes_open(line, i))
		{
			if (i == 0)
				return (0);
			if (line[i + 1] == '\0')
				return (0);
			if (i != 0 && (line[i - 1] == '|' || line[i + 1] == '|'))
				return (0);
		}
	}
	return (1);
}
