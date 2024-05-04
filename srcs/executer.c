/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:18:36 by dmeirele          #+#    #+#             */
/*   Updated: 2024/04/18 17:31:32 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_executer(char *command, char **new_array,
		char **array_env, t_parsed *tokens)
{
	struct stat	path_stat;

	ft_restore_signals();
	stat(command, &path_stat);
	if (execve(command, new_array, array_env) == -1)
	{
		if (strncmp(command, "./", 2) && strncmp(command, "/", 1))
			ft_err_msg(" command not found", 127);
		else if (S_ISDIR(path_stat.st_mode))
			ft_err_msg(" Is a directory", 126);
		else
			ft_err_msg(" command not found", 127);
		free_splits(new_array);
		free_splits(array_env);
		ft_exit(tokens, NULL, NULL, 0);
	}
	else
	{
		free_splits(new_array);
		free_splits(array_env);
		ft_exit(tokens, NULL, NULL, 0);
	}
}

void	ft_save_exit_status(int status, t_envs *envs)
{
	char	*exit_status;
	char	*key;

	exit_status = ft_itoa(status);
	key = ft_strjoin("?=", exit_status);
	envs = ft_add_env(envs, ft_new_env(key));
	free(exit_status);
}

void	ft_err_msg(char *error, int signal)
{
	ft_putendl_fd(error, 2);
	g_signal = signal;
}
