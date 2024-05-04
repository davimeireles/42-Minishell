/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:58:08 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/06 11:21:48 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*aux_dest;
	unsigned char		*aux_src;
	size_t				i;

	aux_dest = (unsigned char *) dest;
	aux_src = (unsigned char *) src;
	i = 1;
	if (dest < src)
		ft_memcpy(dest, src, n);
	else if (dest > src)
	{
		while (i <= n)
		{
			aux_dest[n - i] = aux_src[n - i];
			i++;
		}
	}
	return (dest);
}
