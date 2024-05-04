/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmeirele <dmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:14:57 by dmeirele          #+#    #+#             */
/*   Updated: 2024/02/20 15:14:57 by dmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_command(char *command, t_parsed *tokens);
static char	**ft_count_args(t_parsed *tokens);
static char	*ft_get_absolut_path(char *command, t_envs *envs);

static void	ft_exec_command(char *command, t_parsed *tokens)
{
	t_envs	*envs;
	pid_t	new_process;
	char	**array_env;
	char	**new_array;

	new_array = ft_count_args(tokens);
	envs = return_envs(0);
	array_env = ft_array_envs(envs);
	new_process = fork();
	if (!new_process)
		ft_executer(command, new_array, array_env, tokens);
	ft_ignore_signals();
	waitpid(new_process, &g_signal, 0);
	if (g_signal == 131)
		printf("Quit (core dumped)\n");
	else if (g_signal == 2)
	{
		printf("\n");
		g_signal = 130;
	}
	free(command);
	free_splits(new_array);
	free_splits(array_env);
	ft_init_signals();
}

static char	**ft_count_args(t_parsed *tokens)
{
	int			i;
	char		**new;
	t_parsed	*head;

	i = 0;
	head = tokens;
	while (tokens && tokens->type != PIPE)
	{
		i++;
		tokens = tokens->next;
	}
	new = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (head && head->type != PIPE)
	{
		new[i] = ft_strdup(head->text);
		i++;
		head = head->next;
	}
	new[i] = NULL;
	return (new);
}

static char	*ft_get_absolut_path(char *command, t_envs *envs)
{
	char	**path;
	char	*temp;
	char	*exec;
	int		i;

	i = -1;
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	path = ft_get_path(envs);
	if (!path)
		return (NULL);
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		exec = ft_strjoin(temp, command);
		free(temp);
		if (access(exec, X_OK) == 0)
		{
			free_splits(path);
			return (exec);
		}
		free(exec);
	}
	return (free_splits(path), NULL);
}

void	ft_find_path(t_parsed *token, t_envs *envs)
{
	char	*command;
	char	*path;

	command = ft_strdup(token->text);
	path = NULL;
	path = ft_get_absolut_path(command, envs);
	if (path)
		ft_exec_command(path, token);
	else
	{
		if (access(command, F_OK)
			&& (!strncmp(command, "/", 1) || !strncmp(command, "./", 2)))
			ft_err_msg(" No such file or directory", 127);
		else if (access(command, X_OK)
			&& (!strncmp(command, "/", 1) || !strncmp(command, "./", 2)))
			ft_err_msg(" Permission denied", 126);
		else
			ft_err_msg(" command not found", 127);
	}
	free(command);
}
