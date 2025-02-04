/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:56:13 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/09 22:58:52 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**ft_parse(char const *s);
size_t	f_word_count(char const *str);
size_t	f_word_len(char const *str, char stop);
int		f_alloc_words(char **parsed, char const *s);

char	**ft_parse(char const *s)
{
	char	**parsed;
	size_t	wcount;

	wcount = f_word_count(s);
	parsed = (char **)malloc((wcount + 1) * sizeof(char *));
	if (!parsed)
		return (NULL);
	parsed[wcount] = NULL;
	if (f_alloc_words(parsed, s) == -1)
		return (NULL);
	return (parsed);
}

size_t	f_word_count(char const *str)
{
	size_t	wcount;
	char	skip;

	wcount = 0;
	while (*str)
	{
		skip = ' ';
		if (*str != skip)
		{
			wcount++;
			if (*str == '\"' || *str == '\'')
				skip = *str++;
			while (*str && *str != skip)
				str++;
		}
		if (*str && *str == skip)
			str++;
	}
	return (wcount);
}

size_t	f_word_len(char const *str, char stop)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != stop)
		i++;
	return (i);
}

int	f_alloc_words(char **parsed, char const *s)
{
	size_t	line;
	size_t	word;
	char	skip;

	line = 0;
	while (*s)
	{
		word = 0;
		skip = ' ';
		if (*s != skip)
		{
			if (*s == '\"' || *s == '\'')
				skip = *s++;
			parsed[line] = malloc((f_word_len(s, skip) + 1) * sizeof(char));
			if (!parsed[line])
				return (-1);
			while (*s && *s != skip)
				parsed[line][word++] = *s++;
			parsed[line][word] = '\0';
			line++;
		}
		if (*s && *s == skip)
			s++;
	}
	return (0);
}
