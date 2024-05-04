/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:30:05 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/25 16:24:49 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hexlen(unsigned long n)
{
	int	count;

	count = 0;
	while (n != 0)
	{
		n /= 16;
		count++;
	}
	return (count + 2);
}

static void	ft_putpointer_write(unsigned long n, char *base)
{
	if (n >= 16)
	{
		ft_putpointer_write(n / 16, base);
		ft_putchar(base[n % 16]);
	}
	else
		ft_putchar(base[n % 16]);
}

int	ft_putpointer(unsigned long n)
{
	int	count;

	if (!n)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	count = ft_hexlen(n);
	ft_putstr("0x");
	ft_putpointer_write(n, "0123456789abcdef");
	return (count);
}
