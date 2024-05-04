/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:57:13 by dmeirele          #+#    #+#             */
/*   Updated: 2024/04/18 19:26:18 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_success(char *args, t_envs *envs, char curr_dir[PATH_MAX],
				char old_pwd[PATH_MAX]);
static void	ft_failure(char curr_dir[PATH_MAX], t_envs *envs, char *args);
static void	ft_old_in_failure(t_envs *envs, char curr_dir[PATH_MAX],
				char *helper2, char *helper_pwd);
static void	ft_get_home_dir(t_envs *envs);

void	ft_exec_cd(t_parsed *tokens, t_envs *envs)
{
	char	curr_dir[PATH_MAX];
	char	old_pwd[PATH_MAX];
	char	*args;

	if (tokens && tokens->next)
	{
		ft_putendl_fd(" too many arguments", 2);
		g_signal = 1;
		return ;
	}
	if (tokens)
		args = tokens->text;
	else
		args = NULL;
	if (getcwd(old_pwd, sizeof(old_pwd)))
		ft_success(args, envs, curr_dir, old_pwd);
	else
		ft_failure(curr_dir, envs, args);
}

static void	ft_success(char *args, t_envs *envs, char curr_dir[PATH_MAX],
			char old_pwd[PATH_MAX])
{
	if (args == NULL || !ft_strcmp(args, "~"))
	{
		ft_get_home_dir(envs);
		if (getcwd(curr_dir, sizeof(char [4096])))
			ft_update_curr_dir(envs, curr_dir, old_pwd);
	}
	else if (!ft_strcmp(args, "-"))
	{
		ft_get_oldpwd_dir(envs);
		if (getcwd(curr_dir, sizeof(char [4096])))
			ft_update_curr_dir(envs, curr_dir, old_pwd);
	}
	else if (!chdir(args))
	{
		if (getcwd(curr_dir, sizeof(char [4096])))
			ft_update_curr_dir(envs, curr_dir, old_pwd);
	}
	else
		ft_errno();
}

static void	ft_old_in_failure(t_envs *envs, char curr_dir[PATH_MAX],
				char *helper2, char *helper_pwd)
{
	ft_get_oldpwd_dir(envs);
	if (getcwd(curr_dir, sizeof(char [4096])))
		ft_update_curr_dir(envs, curr_dir, helper2);
	return (free(helper2), free(helper_pwd));
}

static void	ft_failure(char curr_dir[PATH_MAX], t_envs *envs, char *args)
{
	char	*helper_pwd;
	char	*helper2;
	t_envs	*head;

	head = envs;
	while (head)
		ft_while_else(&helper_pwd, &helper2, &head);
	if (args == NULL || !ft_strcmp(args, "~"))
	{
		ft_get_home_dir(envs);
		if (getcwd(curr_dir, sizeof(char [4096])))
			ft_update_curr_dir(envs, curr_dir, helper2);
		return (free(helper2), free(helper_pwd));
	}
	else if (!ft_strcmp(args, "-"))
		return (ft_old_in_failure(envs, curr_dir, helper2, helper_pwd));
	else if (args && !chdir(args) && getcwd(curr_dir, sizeof(char [4096])))
	{
		ft_update_curr_dir(envs, curr_dir, helper2);
		free(helper2);
		free(helper_pwd);
		return ;
	}
	chdir(helper_pwd);
	ft_update_curr_dir(envs, helper_pwd, helper2);
}

static void	ft_get_home_dir(t_envs *envs)
{
	char	*home_dir;

	home_dir = NULL;
	while (envs)
	{
		if (!ft_strcmp(envs->key, "HOME"))
		{
			home_dir = ft_strdup(envs->value);
			break ;
		}
		envs = envs->next;
	}
	if (!chdir(home_dir))
	{
		if (home_dir)
			free(home_dir);
		return ;
	}
	else if (envs && !ft_strcmp(envs->key, "HOME"))
		ft_err_msg(" No such file or directory", 1);
	else
		ft_err_msg(" HOME not set", 1);
	if (home_dir)
		free(home_dir);
}
