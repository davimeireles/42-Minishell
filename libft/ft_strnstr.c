/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:34:17 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/06 11:20:14 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if (*little == '\0' || !little)
		return ((char *) big);
	while (i < len && big[i])
	{
		if (little_len + i > len)
			return (0);
		if (ft_strncmp(&big[i], little, little_len) == 0)
		{
			return ((char *) &big[i]);
		}
		i++;
	}
	return (0);
}
