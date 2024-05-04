/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:06:24 by dmeirele          #+#    #+#             */
/*   Updated: 2024/04/22 15:22:57 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_forced_signal_exit(t_parsed **commands, int total_com,
				int sig_value);
static int	ft_check_numeric_argument(t_parsed *force_signal);

void	ft_exit(t_parsed *tokens, t_parsed *force_signal, t_parsed **commands,
		int total_com)
{
	int	sig_value;

	if (force_signal)
	{
		if (force_signal->next)
		{
			ft_putendl_fd(" too many arguments", 2);
			ft_forced_signal_exit(commands, total_com, 1);
		}
		else if (!ft_check_numeric_argument(force_signal))
		{
			ft_putendl_fd(" numeric argument required", 2);
			ft_forced_signal_exit(commands, total_com, 2);
		}
		sig_value = ft_atoi(force_signal->text);
	}
	else if (WIFEXITED(g_signal))
		sig_value = WEXITSTATUS(g_signal);
	else
		sig_value = g_signal;
	if (tokens)
		ft_free_tokens(tokens);
	ft_forced_signal_exit(commands, total_com, sig_value);
}

static void	ft_forced_signal_exit(t_parsed **commands, int total_com,
		int sig_value)
{
	t_processio	*processio;

	processio = ft_return_processio(NULL);
	ft_free_envs(return_envs(0));
	if (processio)
	{
		free(processio->line);
		processio->line = NULL;
	}
	processio = ft_return_processio(processio);
	if (commands && total_com)
		ft_free_commands(commands, total_com);
	exit(sig_value);
}

static int	ft_check_numeric_argument(t_parsed *force_signal)
{
	int	i;

	i = 0;
	if (force_signal->text[0] == '-' || force_signal->text[0] == '+')
		i++;
	while (force_signal->text[i])
	{
		if (!ft_isdigit(force_signal->text[i]))
			return (0);
		i++;
	}
	return (1);
}
