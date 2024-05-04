/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:57:18 by dmeirele          #+#    #+#             */
/*   Updated: 2024/04/22 21:08:10 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_builtins(t_parsed *tokens, t_parsed **commands, int total_com)
{
	t_envs	*envs;

	envs = return_envs(0);
	g_signal = 0;
	if (!ft_strcmp(tokens->text, "echo") || !ft_strcmp(tokens->text, "\\echo"))
		ft_exec_echo(tokens->next);
	else if (!ft_strcmp(tokens->text, "cd") || !ft_strcmp(tokens->text, "\\cd"))
		ft_exec_cd(tokens->next, envs);
	else if (!ft_strcmp(tokens->text, "pwd")
		|| !ft_strcmp(tokens->text, "\\pwd"))
		ft_exec_pwd();
	else if (!ft_strcmp(tokens->text, "export")
		|| !ft_strcmp(tokens->text, "\\export"))
		envs = ft_exec_export(envs, tokens->next, total_com);
	else if (!ft_strcmp(tokens->text, "unset")
		|| !ft_strcmp(tokens->text, "\\unset"))
		envs = ft_exec_unset(envs, tokens->next, total_com);
	else if (!ft_strcmp(tokens->text, "env")
		|| !ft_strcmp(tokens->text, "\\env"))
		ft_exec_env(envs);
	else if (!ft_strcmp(tokens->text, "exit")
		|| !ft_strcmp(tokens->text, "\\exit"))
		ft_exit(NULL, tokens->next, commands, total_com);
	else
		ft_find_path(tokens, envs);
}
