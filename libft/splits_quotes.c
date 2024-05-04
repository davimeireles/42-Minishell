/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:50:57 by txisto-d          #+#    #+#             */
/*   Updated: 2024/04/18 19:05:17 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char *s, char c)
{
	size_t	i;
	size_t	words;
	int		reading;

	i = 0;
	words = 0;
	reading = 0;
	while (s[i])
	{
		if (!reading && s[i] != c)
		{
			reading = 1;
			words += 1;
		}
		if (reading && s[i] == c && !quotes_open(s, i))
			reading = 0;
		i++;
	}
	return (words);
}

static size_t	ft_word_len(char *orig, char const *s, char c, size_t i_index)
{
	size_t	count;

	count = 0;
	while (s[count])
	{
		if (s[count] == c && !quotes_open(orig, (int)i_index + (int)count))
			break ;
		count++;
	}
	return (count);
}

static char	**ft_clean(char **arr, size_t word)
{
	size_t	i;

	i = 0;
	while (i < word)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

static char	**ft_alloc_write(char *s, char c, char **arr, size_t words)
{
	size_t	i;
	size_t	j;
	size_t	word;

	i = 0;
	word = 0;
	while (word < words)
	{
		j = 0;
		while (s[i] && s[i] == c)
			i++;
		arr[word] = malloc(ft_word_len(s, &s[i], c, i) + 1);
		if (!arr[word])
			return (ft_clean(arr, word));
		while (s[i])
		{
			if (s[i] == c && !quotes_open(s, (int)i))
				break ;
			arr[word][j++] = s[i++];
		}
		arr[word][j] = '\0';
		word++;
	}
	return (arr);
}

char	**split_quotes(char *s, char c)
{
	char	**arr;
	size_t	words;

	words = ft_count_words(s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (0);
	arr[words] = 0;
	if (words > 0)
		arr = ft_alloc_write(s, c, arr, words);
	return (arr);
}
