/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 09:23:57 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/14 09:23:57 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_withminus(t_arg *arg, t_string *string, char *content);
static void	ft_withoutminus(t_arg *arg, t_string *string, char *content);
static void	ft_precessor(t_arg *arg, t_string *string);
static void	ft_finish(t_arg *arg, t_string *string, char *content);

void	ft_print_p(t_arg *arg, t_string *string, va_list lst)
{
	unsigned long	num;
	char			*str;

	num = va_arg(lst, unsigned long);
	if (num)
	{
		str = ft_ptoa(num);
		arg->hash = 1;
	}
	else
	{
		str = ft_strdup("(nil)");
		arg->hash = 0;
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
	ft_precessor(arg, string);
	while (arg->precision > (int) ft_strlen(content))
	{
		ft_printchar('0', string);
		arg->width--;
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
	if ((arg->plus || arg->space) && !arg->zero)
		arg->width--;
	if (arg->hash && !arg->zero)
		arg->width -= 2;
	if (!arg->zero)
	{
		while (arg->width > arg->precision)
		{
			ft_printchar(' ', string);
			arg->width--;
		}
	}
	ft_precessor(arg, string);
	if (arg->zero)
	{
		while (arg->width > arg->precision)
		{
			ft_printchar('0', string);
			arg->width--;
		}
	}
	ft_finish(arg, string, content);
}

static void	ft_finish(t_arg *arg, t_string *string, char *content)
{
	while (arg->precision > (int) ft_strlen(content))
	{
		ft_printchar('0', string);
		arg->precision--;
	}
	while (*content)
		ft_printchar(*content++, string);
}

static void	ft_precessor(t_arg *arg, t_string *string)
{
	if (arg->plus)
	{
		ft_printchar('+', string);
		arg->width--;
	}
	else if (arg->space)
	{
		ft_printchar(' ', string);
		arg->width--;
	}
	if (arg->hash)
	{
		ft_printstr("0x", string);
		arg->width -= 2;
	}
}
