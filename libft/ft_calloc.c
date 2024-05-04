/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:21:20 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/06 11:21:01 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*temp;
	size_t			b_size;
	size_t			i;

	b_size = nmemb * size;
	i = 0;
	temp = malloc(b_size);
	if (temp == NULL)
		return (NULL);
	while (i < b_size)
	{
		temp[i] = 0;
		i++;
	}
	return (temp);
}
