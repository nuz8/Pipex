/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:07:34 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/02 00:05:09 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int		get_binaries(t_pipex *data);
char	**get_paths(char **envp);
char	*ft_strextend(char *s1, char const *s2);
char	*get_binary_path(char *cmd, char **paths);

int	get_binaries(t_pipex *data)
{
	// int		i;
	
	data->paths = get_paths(data->env_vars);
	if (!data->paths)
		return (write(2, "Couldn't get paths", 19), 2);
	
	data->cmd1.str = ft_parse(data->argV[2]);
	if (!data->cmd1.str)
		return (free_fields(data), write(2, "Parse error cmd1\n", 19), 2);
	// i = 0;
	// while (*(data->cmd1.str + i))
	// 	ft_printf("%s\n", *(data->cmd1.str + i++));
	// ft_printf("\n");

	data->cmd2.str = ft_parse(data->argV[3]);
	if (!data->cmd2.str)
		return (free_fields(data), write(2, "Parse error cmd2\n", 19), 2);
	// i = 0;
	// while (*(data->cmd2.str + i))
	// 	ft_printf("%s\n", *(data->cmd2.str + i++));
	// ft_printf("\n");
	// ft_printf("\n");
	
	data->bin_path1 = get_binary_path(data->cmd1.str[0], data->paths);
	if (!data->bin_path1)
		return (free_fields(data), write(2, "Couldn't get path1\n", 19), 2);
		// return (free_fields(data), perror("Command not found"), 3);
	// ft_printf("%s\n", (data->bin_path1));
	
	data->bin_path2 = get_binary_path(data->cmd2.str[0], data->paths);
	if (!data->bin_path2)
		return (free_fields(data), write(2, "Couldn't get path2\n", 19), 2);
		// return (free_fields(data), perror("Command not found"), 3);
	// ft_printf("%s\n", (data->bin_path2));
	// ft_printf("\n");
	return (0);
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

// // The function extends string s1 by appending the contents of string s2 at the
// // the end of s1. The return value is a new string with all characters of s1
// // and s2, while the original string s1 is freed.
// // Not a good practice though, to free a pointer that was allocated before
// // the function call itself.
// char	*ft_strextend(char *s1, char const *s2)
// {
// 	char	*j_str;
// 	size_t	len;
// 	size_t	i;

// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	j_str = (char *)malloc((len + 1) * sizeof(char));
// 	if (!j_str)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		if (i < ft_strlen(s1))
// 			j_str[i] = s1[i];
// 		else
// 			j_str[i] = *s2++;
// 		i++;
// 	}
// 	j_str[i] = '\0';
// 	ft_free_safe(&s1);
// 	s1 = j_str;
// 	return (j_str);
// }

char	*get_binary_path(char *cmd, char **paths)
{
	char	*bin;
	char	*tmp;

	if (access(cmd, F_OK) == 0)
	{
		bin = cmd;
		return (bin);
	}
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (NULL);
		bin = ft_strjoin(tmp, cmd);	// Fixed: Possible memory leaks here due to change of pointers from previous allocation
		if (!bin)
			return (free(tmp), NULL);
		free(tmp);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		paths++;
	}
	return (NULL);
}
