/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:30:53 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/20 15:25:18 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_close(int fd[2]);
void	ft_free_2D(char **memory);
char	**get_paths(char **envp);
char	*get_binary_path(char *cmd, char **paths);
size_t	param_count(char **cmd);
char	*ft_weave(char *str1, char *str2, char separater);
size_t	ft_weave2(char *str1, char *str2, char separater);
char	**ft_parse(char **cmd);

void	ft_close(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_free_2D(char **memory)
{
	size_t	i;

	i = 0;
	while (memory[i] != NULL)
		free(memory[i++]);	
	free(memory);
}

char	**get_paths(char **envp)
{
	char	**paths;
	char	*path;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path = ft_strdup(*envp + 5);
			if (!path)
				return (NULL);
			break ;
		}
		envp++;
	}
	paths = ft_split(path, ':');
	if (!paths)
		return (free(path), NULL);
	return (free(path), paths);
}

char	*get_binary_path(char *cmd, char **paths)
{
	char	*bin;

	while (*paths)
	{
		bin = ft_strjoin(*paths, "/");
		if (!bin)
			return (NULL);
		bin = ft_strjoin(bin, cmd);
		if (!bin)
			return (NULL);
		if (access(bin, F_OK) == 0)
			return (bin);
		paths++;
	}
	return (NULL);
}

// Function that counts the actual number of parameters in an unparsed cmd string
// If double or single quotations are present, the whole string within the quotations is counted as one
size_t	param_count(char **cmd)
{
	size_t	total_words;
	size_t	word_len;
	
	total_words = 0;
	while (*cmd)
	{
		total_words++;
		if ((*cmd)[0] == '\"' || (*cmd)[0] == '\'')
		{
			word_len = ft_strlen(*cmd);
			while ((*cmd)[word_len - 1] != '\"' && (*cmd)[word_len - 1] != '\'')
			{
				cmd++;
				word_len = ft_strlen(*cmd);
			}
		}
		cmd++;
	}
	return (total_words);
}

// // Function to "weave" two strings together separated by the "separator" character.
// // It weaves str1 and str2 together into a new_str, frees the first string and returns the new_string
// char	*ft_weave(char *str1, char *str2, char separater)
// {
// 	char	*new_str;
// 	char	*str1_cpy;
// 	size_t	new_len;
// 	size_t	i;

// 	str1_cpy = str1;
// 	new_len = ft_strlen(str1) + ft_strlen(str2);
// 	if (separater)
// 		new_len++;
// 	new_str = (char *)malloc((new_len + 1) * sizeof(char));
// 	if (!new_str)
// 		return (NULL);
// 	i = 0;
// 	while (*str1)
// 		new_str[i++] = *str1++;
// 		// new_str[i++] = *(*str1)++;
// 	if (separater)
// 		new_str[i++] = separater;
// 	while (str2)
// 		new_str[i++] = *str2++;
// 	new_str[i] = '\0';
// 	return (free(str1_cpy), new_str);
// }

// // Same as ft_weave, but changes the address to which str1 points, and returns the length of the new string.
// // Have to verify that the code works as intended, or a double pointer is required to achieve this
// size_t	ft_weave2(char *str1, char *str2, char separater)
// {
// 	char	*new_str;
// 	char	*str1_cpy;
// 	size_t	new_len;
// 	size_t	i;

// 	str1_cpy = str1;
// 	new_len = ft_strlen(str1) + ft_strlen(str2);
// 	if (separater)
// 		new_len++;
// 	new_str = (char *)malloc((new_len + 1) * sizeof(char));
// 	if (!new_str)
// 		return (NULL);
// 	i = 0;
// 	while (*str1)
// 		new_str[i++] = *str1++;
// 	if (separater)
// 		new_str[i++] = separater;
// 	while (str2)
// 		new_str[i++] = *str2++;
// 	new_str[i] = '\0';
// 	return (free(str1_cpy), str1_cpy = new_str, new_len);
// }

// char	**ft_parse(char **cmd)
// {
// 	char	**parsed_cmd;
// 	size_t	i;

// 	i = param_count((*cmd));
// 	parsed_cmd = (char **)malloc((i + 1) * sizeof(char *));
// 	if (!parsed_cmd)
// 		return (NULL);
// 	parsed_cmd[i] = NULL;
// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i][0] != '\"' && cmd[i][0] != '\'')
// 		{
// 			*parsed_cmd = ft_strdup(cmd[i++]);
// 			if (!(*parsed_cmd++))
// 				return (ft_free_2D(parsed_cmd), NULL);
// 		}
// 		else
// 		{
// 			while (cmd[i])
// 			{
// 				parsed_cmd = ft_weave(parsed_cmd, cmd[i++], ' ');
// 				if (!(*parsed_cmd))
// 					return (ft_free_2D(parsed_cmd), NULL);
// 			}
// 		}
// 	}
// 	return (ft_free_2D(cmd), parsed_cmd);
// }
