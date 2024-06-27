/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_before_optimizing.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:56:13 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/27 20:31:51 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char			**ft_parse0(char const *s);
char			**ft_parse(char const *s);
static size_t	f_word_count(char const *str);
static void		f_word_lengths(char const *str, size_t *wordlens);
size_t			ft_strlen2(char const *str, char stop);
static void		f_write(char **parsed, char const *s);
static int		f_malloc_and_write(char **parsed, char const *s);

char	**ft_parse0(char const *s)
{
	char	**parsed;
	size_t	wcount;
	size_t	*wordlens;
	size_t	i;

	wcount = f_word_count(s);
	wordlens = (size_t *)malloc(wcount * sizeof(size_t));
	if (!wordlens)
		return (NULL);
	parsed = (char **)malloc((wcount + 1) * sizeof(char *));
	if (!parsed)
		return (free(wordlens), NULL);
	f_word_lengths(s, wordlens);
	i = 0;
	while (i < wcount)
	{
		parsed[i] = (char *)malloc((wordlens[i] + 1) * sizeof(char));
		if (!parsed[i])
			return (free(wordlens), ft_free2D(parsed), NULL);
		i++;
	}
	parsed[wcount] = NULL;
	f_write(parsed, s);
	free(wordlens);
	return (parsed);
}	// return (parsed[wcount] = NULL, f_write(parsed, s, c), free(wordlens), parsed);

char	**ft_parse(char const *s)
{
	char	**parsed;
	size_t	wcount;
	// size_t	*wordlens;
	// size_t	i;

	wcount = f_word_count(s);
	// wordlens = (size_t *)malloc(wcount * sizeof(size_t));
	// if (!wordlens)
	// 	return (NULL);
	parsed = (char **)malloc((wcount + 1) * sizeof(char *));
	if (!parsed)
		return (NULL);
		// return (free(wordlens), NULL);
	parsed[wcount] = NULL;
	// f_word_lengths(s, wordlens);
	// i = 0;
	// while (i < wcount)
	// {
	// 	parsed[i] = (char *)malloc((wordlens[i] + 1) * sizeof(char));
	// 	if (!parsed[i])
	// 		return (free(wordlens), ft_free2D(parsed), NULL);
	// 	i++;
	// }
	if (f_malloc_and_write(parsed, s) == -1)
		return (ft_free2D(parsed), NULL);
	// free(wordlens);
	return (parsed);
}	// return (parsed[wcount] = NULL, f_write(parsed, s, c), free(wordlens), parsed);

static size_t	f_word_count(char const *str)
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

static void	f_word_lengths(char const *s, size_t *wordlens)
{
	size_t	length;
	size_t	i;
	char	skip;

	i = 0;
	while (*s)
	{
		length = 0;
		skip = ' ';
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

// arr[0] is the outer loop-counter (i), and arr[1] is the inner loop-counter (j)
static void	f_write(char **parsed, char const *s)
{
	size_t	arr[2];
	char	skip;

	arr[0] = 0;
	while (*s)
	{
		arr[1] = 0;
		skip = ' ';
		if (*s != skip)
		{
			if (*s == '\"' || *s == '\'')
				skip = *s++;
			while (*s && *s != skip)
				parsed[(arr[0])][(arr[1])++] = *s++;
			parsed[(arr[0])][(arr[1])] = '\0';
			(arr[0])++;
		}
		if (*s && *s == skip)
			s++;
	}
}

size_t	ft_strlen2(char const *str, char stop)
{
	size_t	i;
	
	if (!str || !stop)
		return (0);
	i = 0;
	while (str[i] && str[i] != stop)
		i++;
	return (i);
}

// arr[0] is the outer loop-counter (i), and arr[1] is the inner loop-counter (j)
static int	f_malloc_and_write(char **parsed, char const *s)
{
	size_t	arr[2];
	char	skip;

	arr[0] = 0;
	while (*s)
	{
		arr[1] = 0;
		skip = ' ';
		if (*s != skip)
		{
			if (*s == '\"' || *s == '\'')
				skip = *s++;
			parsed[(arr[0])] = malloc((ft_strlen2(s, skip) + 1) * sizeof(char));
			if (!parsed[(arr[0])])
				return (ft_free2D(parsed), -1);
			while (*s && *s != skip)
				parsed[(arr[0])][(arr[1])++] = *s++;
			parsed[(arr[0])][(arr[1])] = '\0';
			(arr[0])++;
		}
		if (*s && *s == skip)
			s++;
	}
	return (0);
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
	str = ft_strdup("awk \'$2 == \"console\" {print $3 \" \" $4 \" \" $5}\'");
	// str = ft_strdup("awk '\''$2 == \"console\" {print $3 " " $4 " " $5}'\''");
	// str = ft_strdup("Is this \"correctly parsed\" or not?");
	ft_printf("%s\n", str);
	
	wcount = f_word_count(str);
	wordlens = malloc(wcount * sizeof(size_t));
	f_word_lengths(str, wordlens);
	ft_printf("%d\n\n", wcount);
	i = 0;
	while (i < wcount)
		ft_printf("%d\n", wordlens[i++]);
	ft_printf("\n");
	
	parsed_str = ft_parse(str);
	ps = parsed_str;
	while (*parsed_str)
	{
		ft_printf(">>%s<<\n", *parsed_str);
		parsed_str++;
	}
	ft_printf("\n");

	free(str);
	ft_free2D(ps);
	return (0);
}
