/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:46:00 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/15 19:38:47 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_c(t_arg *arg, t_string *string, va_list lst)
{
	char	c;

	c = va_arg(lst, int);
	if (arg->minus)
	{
		ft_printchar(c, string);
		while (arg->width > 1)
		{
			ft_printchar(' ', string);
			arg->width--;
		}
	}
	else
	{
		while (arg->width > 1)
		{
			ft_printchar(' ', string);
			arg->width--;
		}
		ft_printchar(c, string);
	}
}
