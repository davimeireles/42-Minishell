/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:00:14 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/23 13:56:02 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_redirects(t_parsed **aux, t_parsed **tokens, int num_com)
{
	tokens[num_com] = *aux;
	if (*aux)
		(*aux)->prev = NULL;
}

void	ft_in_doc(int pipe_fd[2], char *heredoc)
{
	int			status;
	char		*line;
	t_envs		*envs;

	envs = return_envs(NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, heredoc))
			break ;
		line = ft_expand_heredoc(line, envs);
		status = write(pipe_fd[1], line, ft_strlen(line));
		status = write(pipe_fd[1], "\n", 1);
		if (status == -1)
			ft_err_msg("Error writing to pipe", status);
		free(line);
	}
}

char	*ft_expand_heredoc(char *line, t_envs *envs)
{
	long long		i;
	char			*beginner;
	char			*mid;
	char			*final;
	char			*value;

	i = ft_strchr(line, '$') - line + 1;
	beginner = NULL;
	if (i >= 0)
	{
		if (i > 0)
			beginner = ft_substr(line, 0, i - 1);
		value = ft_getenv(&line[i], envs);
		mid = ft_strjoin(beginner, value);
		free(beginner);
		if (line[i + ft_envlen(&line[i])] == '?'
			&& line[i + ft_envlen(&line[i]) - 1] == '$')
			beginner = ft_strdup(&line[i + 1]);
		else
			beginner = ft_strdup(&line[i + ft_envlen(&line[i])]);
		final = ft_strjoin(mid, beginner);
		ft_free_expander(value, beginner, mid, line);
		return (ft_expand_heredoc(final, envs));
	}
	return (line);
}

char	*ft_getenv(char *key, t_envs *envs)
{
	char	*temp;

	temp = ft_substr(key, 0, ft_envlen(key));
	while (envs)
	{
		if (!ft_strcmp(temp, envs->key))
		{
			free(temp);
			return (ft_strdup(envs->value));
		}
		envs = envs->next;
	}
	if (!ft_strncmp(key, "?", 1))
	{
		free(temp);
		if (g_signal > 255)
			return (ft_itoa(WEXITSTATUS(g_signal)));
		return (ft_itoa(g_signal));
	}
	free(temp);
	return (NULL);
}

void	ft_free_expander(char *value, char *beginner, char *mid, char *line)
{
	free(value);
	free(beginner);
	free(mid);
	free(line);
}
