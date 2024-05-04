/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:09:00 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/25 16:24:49 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char	*str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			ft_putchar(str[i++]);
	}
	else
	{
		write(1, "(null)", 6);
		return (6);
	}
	return (i);
}
