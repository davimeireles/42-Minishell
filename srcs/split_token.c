/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:28:12 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/18 17:31:32 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_quotes_len(char *str, size_t *i, size_t *len, char quote)
{
	if (str[*i] == quote)
	{
		(*i)++;
		(*len)++;
		while (str[*i] && str[*i] != quote)
		{
			(*len)++;
			(*i)++;
		}
		if (str[*i] == quote)
		{
			(*len)++;
			(*i)++;
		}
	}
}

static size_t	ft_token_len(char *str, int *start)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = *start;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\''
		&& str[i] != '\"')
	{
		len++;
		i++;
	}
	if (len == 0)
		ft_quotes_len(str, &i, &len, '\"');
	if (len == 0)
		ft_quotes_len(str, &i, &len, '\'');
	if (len != 0)
		*start = i;
	return (len);
}

static void	ft_token_list(char *line, t_parsed *lst, int *i)
{
	size_t		len;
	int			start;
	t_parsed	*aux;

	start = 0;
	len = 0;
	aux = lst;
	while (line[start])
	{
		len = ft_token_len(line, &start);
		start -= len;
		aux->text = ft_substr(line, start, len);
		start += len;
		aux->next = ft_calloc(1, sizeof(t_parsed));
		aux->next->prev = aux;
		if (!aux->next)
			exit(1);
		aux = aux->next;
		(*i)++;
		if ((line[start] == ' ' || line[start] == '\t')
			&& line[start + 1] == '\0')
			start++;
	}
	aux->prev->next = NULL;
	free(aux);
}

t_special	find_type(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strcmp(arg, ">") == 0)
		return (RD_OVERWRITE);
	if (ft_strcmp(arg, ">>") == 0)
		return (RD_APPEND);
	if (ft_strcmp(arg, "<") == 0)
		return (RD_INPUT);
	if (ft_strcmp(arg, "<<") == 0)
		return (RD_HEREDOC);
	if (ft_strcmp(arg, "|") == 0)
		return (PIPE);
	return (STRING);
}

t_parsed	*ft_split_token(char *line)
{
	t_parsed	*aux;
	t_parsed	*head;
	int			i;

	i = 0;
	aux = ft_calloc(1, sizeof(t_parsed));
	if (!aux)
		exit(1);
	head = aux;
	aux->prev = NULL;
	ft_token_list(line, aux, &i);
	aux->type = find_type(aux->text);
	aux = aux->next;
	while (aux)
	{
		aux->type = find_type(aux->text);
		aux = aux->next;
	}
	return (head);
}
