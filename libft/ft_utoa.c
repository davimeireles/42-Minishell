/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:38:56 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/14 10:39:06 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_utlen(long n)
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

char	*ft_utoa(unsigned int n)
{
	char	*uttoed;
	long	num;
	size_t	len;
	size_t	i;

	i = 2;
	num = n;
	len = ft_utlen(num) + 1;
	uttoed = ft_calloc(len, 1);
	if (!uttoed)
		return (NULL);
	if (num < 0)
	{
		uttoed[0] = '-';
		num = -num;
	}
	while (num >= 10)
	{
		uttoed[len - i] = num % 10 + '0';
		num /= 10;
		i++;
	}
	uttoed[len - i] = num + '0';
	return (uttoed);
}
