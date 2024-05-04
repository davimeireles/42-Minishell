/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:20:20 by dmeirele          #+#    #+#             */
/*   Updated: 2024/04/18 19:03:57 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_first_char(char *args);
static void	ft_print_sorted_envs(t_envs *envs);

t_envs	*ft_exec_export(t_envs *envs, t_parsed *tokens, int total_com)
{
	char	*args;

	if (!tokens)
	{
		ft_print_sorted_envs(envs);
		return (envs);
	}
	while (tokens)
	{
		args = tokens->text;
		if (ft_check_first_char(args))
		{
			if (total_com == 1)
				envs = ft_add_env(envs, ft_new_env(args));
			else
				g_signal = 1;
		}
		else
			ft_err_msg(" not a valid identifier", 1);
		tokens = tokens->next;
	}
	return (envs);
}

static int	ft_check_first_char(char *args)
{
	if (!args)
		return (0);
	while (*args == '\"' || *args == '\'')
		args++;
	if (ft_isalpha(*args))
	{
		while (*args != '=' && *args)
		{
			if (*args == '-')
				return (0);
			args++;
		}
		return (1);
	}
	return (0);
}

static void	ft_print_sorted_envs(t_envs *envs)
{
	t_envs	*new;
	char	**new_envs;

	new_envs = ft_array_envs(envs);
	new = 0;
	new = ft_create_envs_for_export(new, new_envs);
	ft_exec_declare_env(new);
	ft_free_envs(new);
	ft_free_array(new_envs);
}
