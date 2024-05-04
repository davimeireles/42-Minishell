/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:54:36 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/25 16:24:49 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_eof(void)
{
	printf("exit\n");
	ft_exit(NULL, NULL, NULL, 0);
}

void	ft_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		g_signal = 130;
	}
}

void	ft_handle_sigint_ign(int sig)
{
	if (sig == SIGINT)
		g_signal = sig;
}

void	ft_handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
		g_signal = sig;
}

void	ft_handle_doc(int sig)
{
	g_signal = sig;
	ft_putchar_fd('\n', 1);
	ft_free_commands(ft_save_commands(NULL), 1);
	ft_free_envs(return_envs(NULL));
	exit(-1);
}
