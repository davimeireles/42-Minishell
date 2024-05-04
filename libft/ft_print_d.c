/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:46:00 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/16 19:25:21 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_withminus(t_arg *arg, t_string *string, char *content, int neg);
static void	ft_withoutminus(t_arg *arg, t_string *string, char *content,
				int neg);
static void	ft_precessor(t_arg *arg, t_string *string, int neg);
static void	ft_finish(t_arg *arg, t_string *string, char *content);

void	ft_print_d(t_arg *arg, t_string *string, va_list lst)
{
	long	num;
	char	*str;
	int		neg;

	neg = 0;
	num = va_arg(lst, int);
	if (num < 0)
	{
		num = -num;
		neg = 1;
	}
	str = ft_utoa(num);
	if (!num && !arg->precision && arg->dot)
	{
		free(str);
		str = ft_strdup("");
	}
	if (arg->precision < (int) ft_strlen(str))
		arg->precision = (int) ft_strlen(str);
	if (arg->minus)
		ft_withminus(arg, string, str, neg);
	else
		ft_withoutminus(arg, string, str, neg);
	free(str);
}

static void	ft_withminus(t_arg *arg, t_string *string, char *content, int neg)
{
	ft_precessor(arg, string, neg);
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

static void	ft_withoutminus(t_arg *arg, t_string *string, char *content,
				int neg)
{
	if ((neg || arg->plus || arg->space) && !arg->zero)
		arg->width--;
	if (!arg->zero)
	{
		while (arg->width > arg->precision)
		{
			ft_printchar(' ', string);
			arg->width--;
		}
	}
	ft_precessor(arg, string, neg);
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

static void	ft_precessor(t_arg *arg, t_string *string, int neg)
{
	if (neg)
	{
		ft_printchar('-', string);
		arg->width--;
	}
	else if (arg->plus)
	{
		ft_printchar('+', string);
		arg->width--;
	}
	else if (arg->space)
	{
		ft_printchar(' ', string);
		arg->width--;
	}
}
