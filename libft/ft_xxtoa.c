/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xxtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:46:06 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/16 19:25:01 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_xtoando(long num, size_t len, size_t i, char *xttoed);

static size_t	ft_xtlen(long n)
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
	while (n >= 16)
	{
		n /= 16;
		len++;
	}
	return (len);
}

char	*ft_xxtoa(unsigned int n)
{
	char	*xttoed;
	long	num;
	size_t	len;
	size_t	i;

	i = 2;
	num = n;
	len = ft_xtlen(num) + 1;
	xttoed = ft_calloc(len, 1);
	if (!xttoed)
		return (NULL);
	ft_xtoando(num, len, i, xttoed);
	return (xttoed);
}

static void	ft_xtoando(long num, size_t len, size_t i, char *xttoed)
{
	char	*hexa;

	hexa = "0123456789ABCDEF";
	if (num < 0)
	{
		xttoed[0] = '-';
		num = -num;
	}
	while (num >= 16)
	{
		xttoed[len - i] = hexa[num % 16];
		num /= 16;
		i++;
	}
	xttoed[len - i] = hexa[num];
}
