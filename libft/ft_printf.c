/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:00:58 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/16 19:10:35 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list		lst;
	size_t		printlen;
	t_string	string;

	string = (t_string){.len = 0};
	va_start(lst, format);
	printlen = ft_printlen(format);
	ft_printstr_ltda(format, &string);
	format += printlen;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			format += ft_converter(format, lst, &string);
		}
		else if (*format)
		{
			printlen = ft_printlen(format);
			ft_printstr_ltda(format, &string);
			format += printlen;
		}
	}
	va_end(lst);
	return (string.len);
}

int	ft_converter(const char *format, va_list lst, t_string *string)
{
	int		flaglen;
	char	*flags;

	flaglen = ft_flaglen(format);
	if (flaglen > 0)
	{
		flags = ft_substr(format, 0, flaglen);
		if (!flags)
			return (0);
	}
	else
		flags = ft_strdup("");
	format += flaglen;
	flaglen += ft_specif(*(format), flags, lst, string);
	free(flags);
	return (flaglen);
}

int	ft_printlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '%')
		i++;
	return (i);
}

int	ft_flaglen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+' || str[i] == ' '
			|| str[i] == '#' || str[i] == '0'))
		i++;
	if (str[i] >= '1' && str[i] <= '9')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
			i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
			i++;
	}
	return (i);
}
