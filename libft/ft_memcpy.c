/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:54:17 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/06 11:21:38 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*aux_src;
	unsigned char		*aux_dest;
	size_t				i;

	i = 0;
	aux_src = (unsigned char *) src;
	aux_dest = dest;
	if (!dest && !src)
		return (dest);
	while (i++ < n)
		*aux_dest++ = *aux_src++;
	return (dest);
}
