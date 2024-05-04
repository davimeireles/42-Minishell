/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:06:18 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/18 17:31:32 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_mslvl(t_envs *envs, char *envp)
{
	char	*mslvl;
	int		value;
	char	*temp;

	value = ft_atoi(&envp[6]);
	value++;
	temp = ft_itoa(value);
	mslvl = ft_strjoin("SHLVL=", temp);
	free(temp);
	ft_add_env(envs, ft_new_env(mslvl));
	free(mslvl);
}
