/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:55:56 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/09 13:53:15 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_map(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	void	*cont;

	if (!lst || !f || !del)
		return (NULL);
	cont = f(lst->content);
	newlst = ft_lstnew(cont);
	if (!newlst)
	{
		del(cont);
		return (NULL);
	}
	return (newlst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*newlst;
	void	*cont;

	map = ft_map(lst, f, del);
	if (!map)
		return (NULL);
	newlst = map;
	lst = lst->next;
	while (lst)
	{
		cont = f(lst->content);
		newlst->next = ft_lstnew(cont);
		if (!newlst->next)
		{
			del(cont);
			ft_lstclear(&map, del);
			return (NULL);
		}
		newlst = newlst->next;
		lst = lst->next;
	}
	newlst->next = NULL;
	return (map);
}
