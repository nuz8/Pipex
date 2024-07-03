/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:56:13 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/03 02:18:50 by pamatya          ###   ########.fr       */
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
		// return (ft_free2d_safe(&parsed), NULL);
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

// line is the outer loop-counter (i), and word is the inner loop-counter (j)
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

// int	main(void)
// {
// 	char	*str;
// 	int		i;
// 	int		wcount;
// 	size_t	*wordlens;
// 	char	**parsed_str;
// 	char	**ps;

// 	// str = ft_strdup("   grep -v \"              this     word  \" and this \'  one right here  \', huh?  ");
// 	// str = ft_strdup("awk \'$2 == \"console\" {print $3 \" \" $4 \" \" $5}\'");
// 	str = ft_strdup("awk '\''$2 == \"console\" {print $3 " " $4 " " $5}'\''");
// 	// str = ft_strdup("Is this \"correctly parsed\" or not?");
// 	ft_printf("%s\n", str);
	
// 	wcount = f_word_count(str);
// 	wordlens = malloc(wcount * sizeof(size_t));
// 	// f_word_lengths(str, wordlens);
// 	ft_printf("%d\n\n", wcount);
// 	i = 0;
// 	// while (i < wcount)
// 	// 	ft_printf("%d\n", wordlens[i++]);
// 	// ft_printf("\n");
	
// 	parsed_str = ft_parse(str);
// 	ps = parsed_str;
// 	while (*parsed_str)
// 	{
// 		ft_printf(">>%s<<\n", *parsed_str);
// 		parsed_str++;
// 	}
// 	ft_printf("\n");

// 	free(str);
// 	ft_free2d(ps);
// 	return (0);
// }
