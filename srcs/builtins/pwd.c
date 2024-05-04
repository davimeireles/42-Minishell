/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 23:15:18 by dmeirele          #+#    #+#             */
/*   Updated: 2024/04/18 17:31:42 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_pwd(void)
{
	t_envs	*envs;
	char	*curr_dir;

	envs = return_envs(0);
	curr_dir = getcwd(0, 0);
	if (!curr_dir)
	{
		while (envs)
		{
			if (!ft_strcmp(envs->key, "PWD"))
			{
				curr_dir = ft_strdup(envs->value);
				printf("%s\n", curr_dir);
			}
			envs = envs->next;
		}
	}
	else
		printf("%s\n", curr_dir);
	free(curr_dir);
}
