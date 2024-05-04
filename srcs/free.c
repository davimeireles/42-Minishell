/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:21:51 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/18 17:31:32 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_commands(t_parsed **commands, int total_com)
{
	int	i;

	i = 0;
	while (i < total_com || commands[i])
	{
		ft_free_tokens(commands[i]);
		i++;
	}
	free(commands);
}

void	ft_free_tokens(t_parsed *tokens)
{
	t_parsed	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->text);
		free(tokens);
		tokens = tmp;
	}
}

t_envs	*ft_free_envs(t_envs *envs)
{
	t_envs	*temp;

	while (envs)
	{
		if (envs->key)
			free(envs->key);
		if (envs->value)
			free(envs->value);
		temp = envs;
		envs = envs->next;
		free(temp);
	}
	return (0);
}

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
