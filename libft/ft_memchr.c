/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:44:53 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/06 11:21:10 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*aux;

	aux = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (aux[i] == (unsigned char) c)
			return (&aux[i]);
		i++;
	}
	return (0);
}
