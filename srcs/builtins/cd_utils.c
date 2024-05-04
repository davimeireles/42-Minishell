/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:07:51 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/18 17:31:42 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_errno(void)
{
	if (errno == 13)
		ft_err_msg(" Permission denied", 1);
	else if (errno == 2)
		ft_err_msg(" No such file or directory", 1);
}

void	ft_while_else(char	**helper_pwd, char	**helper2, t_envs **head)
{
	if (!ft_strcmp((*head)->key, "OLDPWD"))
		*helper_pwd = ft_strdup((*head)->value);
	if (!ft_strcmp((*head)->key, "PWD"))
		*helper2 = ft_strdup((*head)->value);
	(*head) = (*head)->next;
}

void	ft_get_oldpwd_dir(t_envs *envs)
{
	char	*old_dir;

	old_dir = NULL;
	while (envs)
	{
		if (!ft_strcmp(envs->key, "OLDPWD"))
			old_dir = ft_strdup(envs->value);
		envs = envs->next;
	}
	if (!chdir(old_dir))
	{
		if (old_dir)
			free(old_dir);
		return ;
	}
	ft_putendl_fd(" OLDPWD not set", 2);
}

void	ft_update_curr_dir(t_envs *envs, char *curr_dir, char *old_pwd)
{
	char	*pwd;
	char	*old;

	pwd = ft_strjoin("PWD=", curr_dir);
	old = ft_strjoin("OLDPWD=", old_pwd);
	ft_add_env(envs, ft_new_env(pwd));
	ft_add_env(envs, ft_new_env(old));
	free(pwd);
	free(old);
}
