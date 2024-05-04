/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 09:23:57 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/14 10:35:18 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_withminus(t_arg *arg, t_string *string, char *content);
static void	ft_withoutminus(t_arg *arg, t_string *string, char *content);

void	ft_print_u(t_arg *arg, t_string *string, va_list lst)
{
	unsigned int	num;
	char			*str;

	num = va_arg(lst, unsigned int);
	str = ft_utoa(num);
	if (!num && !arg->precision && arg->dot)
	{
		free(str);
		str = ft_strdup("");
	}
	if (arg->precision < (int) ft_strlen(str))
		arg->precision = (int) ft_strlen(str);
	if (arg->minus)
		ft_withminus(arg, string, str);
	else
		ft_withoutminus(arg, string, str);
	free(str);
}

static void	ft_withminus(t_arg *arg, t_string *string, char *content)
{
	while (arg->precision > (int) ft_strlen(content))
	{
		ft_printchar('0', string);
		arg->width--;
		arg->precision--;
	}
	while (*content)
	{
		ft_printchar(*content++, string);
		arg->width--;
	}
	while (arg->width > 0)
	{
		ft_printchar(' ', string);
		arg->width--;
	}
}

static void	ft_withoutminus(t_arg *arg, t_string *string, char *content)
{
	if (!arg->zero)
	{
		while (arg->width > arg->precision)
		{
			ft_printchar(' ', string);
			arg->width--;
		}
	}
	else
	{
		while (arg->width > arg->precision)
		{
			ft_printchar('0', string);
			arg->width--;
		}
	}
	while (arg->precision > (int) ft_strlen(content))
	{
		ft_printchar('0', string);
		arg->precision--;
	}
	while (*content)
		ft_printchar(*content++, string);
}
