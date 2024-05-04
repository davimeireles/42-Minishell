/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:15:14 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/23 13:48:54 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_child(int *pipe_fd, t_processio *processio);
static void	ft_parent(int *pipe_fd, t_processio *processio);

pid_t	ft_pipe(t_processio *processio)
{
	int		pipe_fd[2];
	int		status;
	pid_t	pid;

	pid = 0;
	processio->redirect_signal = 0;
	if (processio->num_com < processio->total_com - 1)
	{
		processio->redirect_fd = ft_redirect(processio, 0);
		status = pipe(pipe_fd);
		if (status == -1)
			ft_printf("Error creating pipe\n");
		pid = fork();
		if (pid == 0)
		{
			ft_child(pipe_fd, processio);
			processio->num_com++;
			pid = ft_pipe(processio);
		}
		else
			ft_parent(pipe_fd, processio);
	}
	else
		ft_finish_redirect(processio);
	return (pid);
}

static void	ft_parent(int *pipe_fd, t_processio *processio)
{
	close(pipe_fd[0]);
	if (processio->redirect_signal == 0)
		dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
}

static void	ft_child(int *pipe_fd, t_processio *processio)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	processio->parent_pid = 0;
}

pid_t	ft_manage_heredoc(int pipe_fd[2], char *heredoc, t_processio *processio)
{
	pid_t	pid;

	pid = fork();
	ft_ignore_signals();
	if (pid == 0)
	{
		ft_save_commands(processio->commands);
		ft_doc_signals();
		dup2(processio->std_fd[0], 0);
		dup2(processio->std_fd[1], 1);
		ft_in_doc(pipe_fd, heredoc);
		ft_free_commands(processio->commands, 1);
		free(processio->line);
		ft_exit(NULL, NULL, NULL, 0);
	}
	else
		waitpid(pid, &g_signal, 0);
	if (g_signal != 65280)
		dup2(pipe_fd[0], 0);
	else
		pid = -2;
	ft_init_signals();
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (pid);
}

int	valid_tokens(t_parsed *tokens)
{
	int			type;
	t_parsed	*aux;

	aux = tokens;
	while (tokens)
	{
		type = tokens->type;
		if (type == PIPE)
		{
			if (!tokens->next || !tokens->prev || tokens->next->type == PIPE)
			{
				ft_putendl_fd("Invalid Pipe", 2);
				g_signal = 2;
				return (0);
			}
		}
		else if (type != STRING)
		{
			if (!tokens->next || tokens->next->type != STRING)
				return (ft_syntax_error(aux));
		}
		tokens = tokens->next;
	}
	return (1);
}
