/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:03:57 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/16 19:01:53 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printstr(const char *s, t_string *string)
{
	while (*s)
		ft_printchar(*s++, string);
}

void	ft_printstr_ltda(const char *s, t_string *string)
{
	while (*s && *s != '%')
		ft_printchar(*s++, string);
}
