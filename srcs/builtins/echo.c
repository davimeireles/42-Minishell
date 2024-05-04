/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:33:04 by dmeirele          #+#    #+#             */
/*   Updated: 2024/04/18 17:31:42 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_echo_arguments(char *array_args);
static void	ft_print_echo_space(t_parsed *aux);
static void	ft_print_new_line(int flag_nl);

void	ft_exec_echo(t_parsed *tokens)
{
	t_parsed	*aux;
	int			flag_nl;
	int			option;

	aux = tokens;
	option = 1;
	flag_nl = 1;
	while (aux)
	{
		if (ft_check_echo_arguments(aux->text) && option)
		{
			flag_nl = 0;
			aux = aux->next;
		}
		else
			option = 0;
		if (!option)
		{
			ft_putstr_fd(aux->text, 1);
			ft_print_echo_space(aux);
			aux = aux->next;
		}
	}
	ft_print_new_line(flag_nl);
}

static int	ft_check_echo_arguments(char *array_args)
{
	int	i;

	i = 0;
	if (array_args[i] != '-')
		return (0);
	i++;
	if (array_args[i] != 'n')
		return (0);
	while (array_args[i] == 'n')
		i++;
	if (array_args[i] != '\0')
		return (0);
	return (1);
}

static void	ft_print_echo_space(t_parsed *aux)
{
	if (aux->next)
		ft_putstr_fd(" ", 1);
	return ;
}

static void	ft_print_new_line(int flag_nl)
{
	if (flag_nl)
		ft_putstr_fd("\n", 1);
	return ;
}
