/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:14:28 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/07 09:49:36 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itlen(long n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		len = 2;
		n = -n;
	}
	else
		len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ittoed;
	long	num;
	size_t	len;
	size_t	i;

	i = 2;
	num = n;
	len = ft_itlen(num) + 1;
	ittoed = ft_calloc(len, 1);
	if (!ittoed)
		return (NULL);
	if (num < 0)
	{
		ittoed[0] = '-';
		num = -num;
	}
	while (num >= 10)
	{
		ittoed[len - i] = num % 10 + '0';
		num /= 10;
		i++;
	}
	ittoed[len - i] = num + '0';
	return (ittoed);
}
