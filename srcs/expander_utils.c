/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:55:56 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/22 16:10:24 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_before_exp(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (i);
}

int	ft_prev_is_redirect(t_parsed *aux)
{
	if (aux->prev == NULL)
		return (0);
	else if (aux->prev->type == RD_OVERWRITE
		|| aux->prev->type == RD_APPEND
		|| aux->prev->type == RD_INPUT
		|| aux->prev->type == RD_HEREDOC)
		return (1);
	else
		return (0);
}

void	ft_null_text(t_parsed **aux, t_parsed **tokens,
			t_parsed **to_free, char *line)
{
	if (*(*aux)->text == '\0')
	{
		if ((*aux)->next == NULL && (*aux)->prev == NULL)
			free(line);
		if ((*aux)->prev)
			(*aux)->prev->next = (*aux)->next;
		else
			*tokens = (*aux)->next;
		if ((*aux)->next)
			(*aux)->next->prev = (*aux)->prev;
		free((*aux)->text);
		*to_free = (*aux);
		(*aux) = (*aux)->next;
	}
}

void	ft_init_temp(t_parsed *tokens, int *klen, char **point, char **tmp)
{
	int		before_len;

	before_len = ft_before_exp(tokens->text);
	*tmp = ft_substr(tokens->text, 0, before_len);
	*klen = ft_key_len(tokens->text);
	*point = tokens->text + before_len + 1;
}
