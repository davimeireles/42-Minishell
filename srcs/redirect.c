/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:08:49 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/24 19:12:19 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_write_append(t_parsed **aux, t_parsed **tokens,
				int num_com, int flag);
static int	ft_input(t_parsed **aux, t_parsed **tokens, int num_com);
static int	ft_doc(t_parsed **aux, t_processio *processio);

static int	ft_what_red(t_parsed **aux, t_processio *processio, int error)
{
	int	fd;

	fd = 1;
	if ((*aux)->type == RD_OVERWRITE && !error)
	{
		fd = ft_write_append(&(*aux), processio->commands,
				processio->num_com, O_WRONLY | O_CREAT | O_TRUNC);
		processio->redirect_signal = 1;
	}
	else if ((*aux)->type == RD_APPEND && !error)
	{
		fd = ft_write_append(&(*aux), processio->commands,
				processio->num_com, O_WRONLY | O_CREAT | O_APPEND);
		processio->redirect_signal = 1;
	}
	else if ((*aux)->type == RD_INPUT)
		fd = ft_input(&(*aux), processio->commands, processio->num_com);
	else if ((*aux)->type == RD_HEREDOC)
		fd = ft_doc(&(*aux), processio);
	return (fd);
}

int	ft_redirect(t_processio *processio, int error)
{
	t_parsed	*aux;
	int			fd;

	fd = 0;
	aux = processio->commands[processio->num_com];
	while (aux && aux->next)
	{
		if (error == 0)
			fd = ft_what_red(&aux, processio, 0);
		else if (error == 1)
			fd = ft_what_red(&aux, processio, 1);
		if (fd <= -1)
		{
			if (errno == 13 && error == 0)
				ft_err_msg(" Permission denied", 1);
			else if (error == 0)
				ft_err_msg(" No such file or directory", 1);
			ft_redirect(processio, 1);
			return (-1);
		}
		if (aux && aux->next && fd == 1)
			aux = aux->next;
	}
	return (fd);
}

static int	ft_write_append(t_parsed **aux, t_parsed **tokens,
				int num_com, int flag)
{
	int			fd;
	t_parsed	*tmp;
	t_parsed	*free_me;

	tmp = (*aux)->prev;
	free_me = *aux;
	*aux = (*aux)->next->next;
	fd = open(free_me->next->text, flag, 0644);
	if (fd != -1)
	{
		dup2(fd, 1);
		close(fd);
	}
	free_me->next->next = NULL;
	if (tmp)
	{
		tmp->next = *aux;
		if ((*aux))
			(*aux)->prev = tmp;
	}
	else
		ft_delete_redirects(aux, tokens, num_com);
	ft_free_tokens(free_me);
	*aux = tokens[num_com];
	return (fd);
}

static int	ft_input(t_parsed **aux, t_parsed **tokens, int num_com)
{
	int			fd;
	t_parsed	*tmp;
	t_parsed	*free_me;

	tmp = (*aux)->prev;
	free_me = *aux;
	*aux = (*aux)->next->next;
	fd = open(free_me->next->text, O_RDONLY);
	if (fd != -1)
	{
		dup2(fd, 0);
		close(fd);
	}
	free_me->next->next = NULL;
	if (tmp)
	{
		tmp->next = *aux;
		if ((*aux))
			(*aux)->prev = tmp;
	}
	else
		ft_delete_redirects(aux, tokens, num_com);
	ft_free_tokens(free_me);
	*aux = tokens[num_com];
	return (fd);
}

static int	ft_doc(t_parsed **aux, t_processio *processio)
{
	int			pipe_fd[2];
	int			i;
	t_parsed	*tmp;
	t_parsed	*free_me;
	pid_t		pid;

	tmp = (*aux)->prev;
	free_me = *aux;
	*aux = (*aux)->next->next;
	i = pipe(pipe_fd);
	if (i == -1)
		ft_putendl_fd("Error creating pipe", 2);
	pid = ft_manage_heredoc(pipe_fd, free_me->next->text, processio);
	free_me->next->next = NULL;
	if (tmp)
	{
		tmp->next = *aux;
		if ((*aux))
			(*aux)->prev = tmp;
	}
	else
		ft_delete_redirects(aux, processio->commands, processio->num_com);
	ft_free_tokens(free_me);
	return (pid);
}
