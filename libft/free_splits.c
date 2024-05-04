/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_splits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hescoval <hescoval@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:15:48 by hescoval          #+#    #+#             */
/*   Updated: 2024/02/09 21:38:43 by hescoval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_splits(char **line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
		free(line[i++]);
	free(line);
	return (0);
}
