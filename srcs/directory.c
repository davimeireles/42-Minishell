/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:29:26 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/18 17:31:32 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_dir(void)
{
	char	*dir;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		tmp = ft_get_pwd_env();
	dir = ft_strjoin \
	("\001\033[1;32m\002minishell@42\001\033[0m\002:\001\033[1;34m\002", tmp);
	free(tmp);
	tmp = ft_strjoin(dir, "\001\033[0m\002$ ");
	free(dir);
	return (tmp);
}

char	**ft_get_path(t_envs *envs)
{
	char	*value;
	char	**path_value;

	path_value = NULL;
	value = NULL;
	if (!envs)
		return (NULL);
	while (envs)
	{
		if (!ft_strncmp(envs->key, "PATH", 4))
			value = ft_substr(envs->value, 0, ft_strlen(envs->value));
		envs = envs->next;
	}
	if (value)
	{
		path_value = ft_split(value, ':');
		free(value);
	}
	return (path_value);
}

char	*ft_get_pwd_env(void)
{
	char	*tmp;
	t_envs	*envs;

	envs = return_envs(NULL);
	while (envs)
	{
		if (!ft_strncmp(envs->key, "PWD", 3))
		{
			tmp = ft_strdup(envs->value);
			return (tmp);
		}
		envs = envs->next;
	}
	return (NULL);
}
