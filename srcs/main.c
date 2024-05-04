/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:18:56 by dmeirele          #+#    #+#             */
/*   Updated: 2024/04/25 16:33:02 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1 && argv)
	{
		ft_printf("This program does not accept any arguments.\n");
		return (1);
	}
	ft_init_signals();
	return_envs(ft_create_envs(envp));
	ft_minishell();
	return (0);
}

void	ft_retrieve_io(t_processio *processio)
{
	dup2(processio->std_fd[0], 0);
	dup2(processio->std_fd[1], 1);
	close(processio->std_fd[0]);
	close(processio->std_fd[1]);
}

void	ft_finish_redirect(t_processio *processio)
{
	dup2(processio->std_fd[1], 1);
	processio->redirect_fd = ft_redirect(processio, 0);
}
