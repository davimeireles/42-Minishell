/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:46:00 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/16 19:02:02 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_withminus(t_arg *arg, t_string *string, char *content);
static void	ft_withoutminus(t_arg *arg, t_string *string, char *content);

void	ft_print_s(t_arg *arg, t_string *string, va_list lst)
{
	char	*content;
	int		contentlen;

	content = va_arg(lst, char *);
	if (!content)
	{
		if (arg->dot && arg->precision < 6)
			content = "";
		else
			content = "(null)";
	}
	contentlen = ft_strlen(content);
	if (arg->precision < 0 || arg->precision > contentlen)
		arg->precision = contentlen;
	if (arg->minus)
		ft_withminus(arg, string, content);
	else
		ft_withoutminus(arg, string, content);
}

static void	ft_withminus(t_arg *arg, t_string *string, char *content)
{
	while (arg->precision > 0 && *content)
	{
		ft_printchar(*content++, string);
		arg->width--;
		arg->precision--;
	}
	while (arg->width > 0)
	{
		ft_printchar(' ', string);
		arg->width--;
	}
}

static void	ft_withoutminus(t_arg *arg, t_string *string, char *content)
{
	while (arg->width > arg->precision)
	{
		ft_printchar(' ', string);
		arg->width--;
	}
	while (arg->precision > 0 && *content)
	{
		ft_printchar(*content++, string);
		arg->precision--;
	}
}
