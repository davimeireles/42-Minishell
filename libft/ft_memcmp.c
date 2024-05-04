/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:50:42 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/05 14:31:18 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*aux1;
	const unsigned char	*aux2;
	size_t				i;
	int					ans;

	aux1 = s1;
	aux2 = s2;
	i = 0;
	if (n == 0)
		return (0);
	while (aux1[i] == aux2[i] && i < n - 1)
		i++;
	ans = aux1[i] - aux2[i];
	if (ans > 0)
		return (1);
	else if (ans < 0)
		return (-1);
	else
		return (0);
}
