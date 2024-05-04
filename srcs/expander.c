/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:12:17 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/23 12:49:35 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_quotes_and_exp(char *str);

t_parsed	*ft_expand_variables(t_parsed *tokens, char *line)
{
	t_envs		*envs;
	t_parsed	*aux;
	t_parsed	*to_free;

	aux = tokens;
	while (aux && aux->text)
	{
		to_free = NULL;
		while (aux && ft_check_quotes_and_exp(aux->text))
		{
			envs = return_envs(0);
			if (ft_prev_is_redirect(aux))
				break ;
			aux->text = ft_expand_heredoc(aux->text, envs);
			ft_null_text(&aux, &tokens, &to_free, line);
		}
		if (!to_free)
			aux = aux->next;
		free(to_free);
	}
	return (tokens);
}

size_t	ft_envlen(char	*str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (ft_isalnum(str[i]))
		i++;
	return (i);
}

int	ft_key_len(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
		i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
	{
		i++;
		j++;
	}
	return (j);
}

static int	ft_check_quotes_and_exp(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\'')
		return (0);
	while (str[i])
	{
		if (str[i] == '$'
			&& (!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == '\"'))
			return (0);
		else if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
