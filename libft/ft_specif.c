/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:59:03 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/16 19:48:55 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_speccheck(char *flags, t_arg *arg);
static void	ft_precision(char *flags, t_arg *arg);
static int	ft_gospec(t_arg *arg, char *flags, va_list lst,
				t_string *string);

int	ft_specif(const char specifier, char *flags, va_list lst, t_string *string)
{
	t_arg	arg;

	arg = (t_arg){.minus = 0, .zero = 0, .plus = 0, .space = 0, .hash = 0,
		.width = -1, .dot = 0, .precision = -1, .specifier = specifier};
	ft_speccheck(flags, &arg);
	return (ft_gospec(&arg, flags, lst, string));
}

static int	ft_gospec(t_arg *arg, char *flags, va_list lst,
		t_string *string)
{
	if (arg->specifier == '%')
		ft_printchar(arg->specifier, string);
	else if (arg->specifier == 'c')
		ft_print_c(arg, string, lst);
	else if (arg->specifier == 's')
		ft_print_s(arg, string, lst);
	else if (arg->specifier == 'p')
		ft_print_p(arg, string, lst);
	else if (arg->specifier == 'd' || arg->specifier == 'i')
		ft_print_d(arg, string, lst);
	else if (arg->specifier == 'u')
		ft_print_u(arg, string, lst);
	else if (arg->specifier == 'x')
		ft_print_x(arg, string, lst);
	else if (arg->specifier == 'X')
		ft_print_xx(arg, string, lst);
	else
	{
		ft_printchar('%', string);
		ft_printstr(flags, string);
		return (0);
	}
	return (1);
}

static void	ft_speccheck(char *flags, t_arg *arg)
{
	while (*flags && (*flags < '1' || *flags > '9') && *flags != '.')
	{
		if (*flags == '-')
			arg->minus = 1;
		if (*flags == '+')
			arg->plus = 1;
		if (*flags == ' ')
			arg->space = 1;
		if (*flags == '0')
			arg->zero = 1;
		if (*flags == '#')
			arg->hash = 1;
		flags++;
	}
	if (arg->plus == 1)
		arg->space = 0;
	if (arg->minus == 1)
		arg->zero = 0;
	if (*flags && *flags >= '0' && *flags <= '9')
		arg->width = ft_atoi(flags);
	while (*flags >= '0' && *flags <= '9')
		flags++;
	if (*flags == '.')
		ft_precision(flags, arg);
}

static void	ft_precision(char *flags, t_arg *arg)
{
	while (*flags && *flags != '.')
		flags++;
	if (*flags == '.')
	{
		arg->dot = 1;
		arg->precision = 0;
		arg->zero = 0;
		flags++;
	}
	if (*flags && *flags >= '0' && *flags <= '9')
		arg->precision = ft_atoi(flags);
}
