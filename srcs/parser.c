/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:19:50 by dmeirele          #+#    #+#             */
/*   Updated: 2024/04/22 21:14:29 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parsed	**ft_commands(t_parsed *tokens, int *num_com);
static int		ft_count_pipe(t_parsed *tokens);
static void		ft_overpipe(t_parsed **tokens, int *num_com);
static void		ft_disconect(t_parsed *aux);

void	ft_parser(t_parsed *tokens, char *line)
{
	t_parsed	**commands;
	t_processio	processio;

	processio.line = line;
	processio.parent_pid = 1;
	processio.std_fd[0] = dup(0);
	processio.std_fd[1] = dup(1);
	commands = ft_commands(tokens, &processio.total_com);
	processio.commands = commands;
	processio.num_com = 0;
	processio.child_pid = ft_pipe(&processio);
	ft_return_processio(&processio);
	if (processio.redirect_fd != -1 && commands[processio.num_com])
		ft_exec_builtins(commands[processio.num_com],
			commands, processio.total_com);
	ft_retrieve_io(&processio);
	ft_free_commands(commands, processio.total_com);
	if (processio.child_pid)
		waitpid(processio.child_pid, &g_signal, 0);
	if (processio.parent_pid != 1)
		ft_exit(NULL, NULL, NULL, 0);
	ft_return_processio(&processio);
}

static t_parsed	**ft_commands(t_parsed *tokens, int *num_com)
{
	t_parsed	*aux;
	t_parsed	**commands;
	int			i;

	aux = tokens;
	*num_com = ft_count_pipe(tokens);
	commands = ft_calloc(*num_com + 1, sizeof(t_parsed *));
	i = 0;
	commands[i++] = aux;
	while (aux)
	{
		if (aux->type == RD_OVERWRITE && aux->next && aux->next->type == PIPE)
			ft_overpipe(&aux, num_com);
		else if (aux->type == PIPE)
		{
			commands[i] = aux->next;
			ft_disconect(aux);
			aux = commands[i++];
		}
		else
			aux = aux->next;
	}
	return (commands);
}

static void	ft_disconect(t_parsed *aux)
{
	aux->prev->next = NULL;
	aux->next->prev = NULL;
	aux->next = NULL;
	ft_free_tokens(aux);
}

static void	ft_overpipe(t_parsed **tokens, int *num_com)
{
	t_parsed	*pipe_token;

	pipe_token = (*tokens)->next;
	(*tokens)->next = pipe_token->next;
	(*tokens)->next->prev = *tokens;
	free(pipe_token->text);
	free(pipe_token);
	(*num_com)--;
}

static int	ft_count_pipe(t_parsed *tokens)
{
	int	i;

	i = 1;
	while (tokens)
	{
		if (tokens->type == PIPE)
			i++;
		tokens = tokens->next;
	}
	return (i);
}
