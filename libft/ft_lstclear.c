/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:42:21 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/07 14:15:01 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nextnode;

	if ((lst))
	{
		while ((*lst))
		{
			nextnode = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = nextnode;
		}
	}
}
