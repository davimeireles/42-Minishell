/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:18:28 by dmeirele          #+#    #+#             */
/*   Updated: 2024/04/18 17:31:32 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envs	*ft_create_envs(char **envp)
{
	t_envs	*envs;

	envs = 0;
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (!ft_strncmp(*envp, "SHLVL=", 6))
			ft_mslvl(envs, *envp);
		else
			envs = ft_add_env(envs, ft_new_env(*envp));
		envp++;
	}
	return (envs);
}

t_envs	*ft_new_env(char *str)
{
	t_envs	*envs;
	int		len;

	envs = malloc(sizeof(t_envs));
	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	envs->key = malloc(len + 1);
	ft_strlcpy(envs->key, str, len + 1);
	if (str[len])
	{
		str += len + 1;
		len = ft_strlen(str);
		len++;
		envs->value = malloc(len);
		ft_strlcpy(envs->value, str, len);
	}
	else
		envs->value = NULL;
	envs->next = 0;
	return (envs);
}

t_envs	*ft_add_env(t_envs *envs, t_envs *new)
{
	t_envs	*start;

	start = 0;
	if (envs && new)
	{
		start = envs;
		while (envs->next && ft_strcmp(envs->key, new->key))
			envs = envs->next;
		if (!ft_strcmp(envs->key, new->key))
		{
			free(envs->value);
			if (new->value)
				envs->value = new->value;
			free(new->key);
			free(new);
			return (start);
		}
		envs->next = new;
		return (start);
	}
	else if (new)
		return (new);
	return (0);
}

char	**ft_array_envs(t_envs *envs)
{
	t_envs	*start;
	int		len;
	char	*temp;
	char	**arr;

	len = 1;
	start = envs;
	while (envs && len++)
		envs = envs->next;
	arr = malloc(sizeof(char *) * len);
	len = 0;
	while (start)
	{
		temp = ft_strjoin(start->key, "=");
		if (start->value)
			arr[len] = ft_strjoin(temp, start->value);
		else
			arr[len] = ft_strdup((start->key));
		free(temp);
		len++;
		start = start->next;
	}
	arr[len] = 0;
	return (arr);
}

t_envs	*ft_create_envs_for_export(t_envs *new, char **new_envs)
{
	t_envs	*start;
	char	*helper_value;
	char	*helper_key;

	new = ft_return_new_env(new, new_envs);
	start = new;
	while (new->next)
	{
		if (ft_strcmp(new->next->key, new->key) < 0)
		{
			helper_key = new->next->key;
			helper_value = new->next->value;
			new->next->key = new->key;
			new->next->value = new->value;
			new->value = helper_value;
			new->key = helper_key;
			new = start;
			continue ;
		}
		new = new->next;
	}
	return (start);
}
