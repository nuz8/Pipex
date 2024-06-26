/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:56:13 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/27 01:45:57 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char			**ft_parse(char const *s, char c);
static size_t	f_word_count(char const *str, char c);
static void		f_word_lengths(char const *str, char c, size_t *wordlens);
static void		f_write(char **parsed, char const *s, char c);

char	**ft_parse(char const *s, char c)
{
	char	**parsed;
	size_t	wcount;
	size_t	*wordlens;
	size_t	i;

	wcount = f_word_count(s, c);
	wordlens = (size_t *)malloc(wcount * sizeof(size_t));
	if (!wordlens)
		return (NULL);
	parsed = (char **)malloc((wcount + 1) * sizeof(char *));
	if (!parsed)
		return (free(wordlens), NULL);
	f_word_lengths(s, c, wordlens);
	i = 0;
	while (i < wcount)
	{
		parsed[i] = (char *)malloc((wordlens[i] + 1) * sizeof(char));
		if (!parsed[i])
			return (free(wordlens), ft_free2D(parsed), NULL);
		i++;
	}
	parsed[wcount] = NULL;
	f_write(parsed, s, c);
	free(wordlens);
	return (parsed);
}	// return (parsed[wcount] = NULL, f_write(parsed, s, c), free(wordlens), parsed);

static size_t	f_word_count(char const *str, char c)
{
	size_t	wcount;
	char	skip;

	wcount = 0;
	while (*str)
	{
		skip = c;
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

static void	f_word_lengths(char const *s, char c, size_t *wordlens)
{
	size_t	length;
	size_t	i;
	char	skip;

	i = 0;
	while (*s)
	{
		length = 0;
		skip = c;
		if (*s != skip)
		{
			if (*s == '\"' || *s == '\'')
				skip = *s++;
			while (*s && *s != skip)
			{
				length++;
				s++;
			}
			wordlens[i] = length;
			i++;
		}
		if (*s && *s == skip)
			s++;
	}
}

static void	f_write(char **parsed, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	length;
	char	skip;

	i = 0;
	while (*s)
	{
		j = 0;
		length = 0;
		skip = c;
		if (*s != skip)
		{
			if (*s == '\"' || *s == '\'')
				skip = *s++;
			while (*s && *s != skip)
				parsed[i][j++] = *s++;
			parsed[i][j] = '\0';
			i++;
		}
		if (*s && *s == skip)
			s++;
	}
}

int	main(void)
{
	char	*str;
	int		i;
	int		wcount;
	size_t	*wordlens;
	char	**parsed_str;
	char	**ps;

	// str = ft_strdup("   grep -v \"              this     word  \" and this \'  one right here  \', huh?  ");
	str = ft_strdup("   grep -v \"this word\" is good \"and this\" one?   ");

	wcount = f_word_count(str, ' ');
	wordlens = malloc(wcount * sizeof(size_t));
	f_word_lengths(str, ' ', wordlens);
	ft_printf("%d\n\n", wcount);
	i = 0;
	while (i < wcount)
		ft_printf("%d\n", wordlens[i++]);
	ft_printf("\n");
	
	parsed_str = ft_parse(str, ' ');
	ps = parsed_str;
	while (*parsed_str)
	{
		ft_printf(">>%s<<\n", *parsed_str);
		parsed_str++;
	}

	free(str);
	ft_free2D(ps);
	return (0);
}
