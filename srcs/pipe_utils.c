/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:04:23 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/22 20:57:11 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_error(t_parsed *tokens)
{
	ft_putendl_fd(" syntax error near unexpected token `newline'",
		2);
	ft_free_tokens(tokens);
	g_signal = 2;
	return (0);
}
