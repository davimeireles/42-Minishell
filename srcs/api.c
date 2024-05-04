/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:18:10 by dmeirele          #+#    #+#             */
/*   Updated: 2024/04/25 16:32:46 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envs	*return_envs(t_envs *envs)
{
	static t_envs	*static_envs;

	if (envs)
		static_envs = envs;
	return (static_envs);
}

t_processio	*ft_return_processio(t_processio *processio)
{
	static t_processio	*static_processio = NULL;

	if (processio == static_processio)
	{
		static_processio = NULL;
		return (NULL);
	}
	if (processio)
		static_processio = processio;
	return (static_processio);
}
