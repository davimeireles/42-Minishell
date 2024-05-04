/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 08:32:59 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/11 16:40:31 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = ft_calloc(s1_len + s2_len + 1, 1);
	if (!joined)
		return (NULL);
	if (s1)
		ft_strlcpy(joined, s1, s1_len + 1);
	if (s2)
		ft_strlcat(joined, s2, s1_len + s2_len + 1);
	return (joined);
}
