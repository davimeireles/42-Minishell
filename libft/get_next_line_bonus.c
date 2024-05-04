/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:40:16 by txisto-d          #+#    #+#             */
/*   Updated: 2024/01/22 17:40:50 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*getting[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	getting[fd] = ft_getting(fd, getting[fd]);
	if (!getting[fd])
		return (NULL);
	line = ft_cut(getting[fd]);
	getting[fd] = ft_update(getting[fd]);
	return (line);
}

char	*ft_getting(int fd, char *getting)
{
	ssize_t	re;
	char	*aux;

	re = 1;
	aux = malloc(BUFFER_SIZE + 1);
	if (!aux)
		return (NULL);
	while (re && !ft_eol(getting))
	{
		re = read(fd, aux, BUFFER_SIZE);
		if (re < 0)
		{
			if (getting)
				free(getting);
			free(aux);
			return (NULL);
		}
		aux[re] = '\0';
		getting = ft_strjoin_nl(getting, aux);
		if (!getting)
			return (NULL);
	}
	free(aux);
	return (getting);
}

char	*ft_cut(char *getting)
{
	size_t	len;
	char	*cutted;

	if (!*getting)
		return (NULL);
	len = ft_linelen(getting);
	cutted = malloc(len + 1);
	if (!cutted)
		return (NULL);
	cutted = ft_strncpy(cutted, getting, len);
	return (cutted);
}

char	*ft_update(char *old)
{
	char	*new;
	size_t	len;
	char	*freeme;

	len = ft_linelen(old);
	freeme = old;
	if (!old[len])
	{
		free(old);
		return (NULL);
	}
	old += len;
	len = ft_strlen(old);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	new = ft_strncpy(new, old, len);
	if (freeme)
		free(freeme);
	return (new);
}

/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd[2];
	char	*line;

	fd[0] = open("teste.txt", O_RDONLY);
	fd[1] = open("bonus.txt", O_RDONLY);
	if (fd[0] == -1)
		printf("teste error\n");
	else
	{
		line = get_next_line(fd[0]);
		printf("%s", line);
		free(line);
	}
	if (fd[1] == -1)
		printf("bonus error\n");
	else
	{
		line = get_next_line(fd[1]);
		printf("%s", line);
		free(line);
	}
	return (0);
}
*/
