/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:07:34 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/30 00:12:33 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int		get_binaries(t_pipex *data);
char	**get_paths(char **envp);
char	*get_binary_path(char *cmd, char **paths);

int	get_binaries(t_pipex *data)
{
	int		i;
	
	data->paths = get_paths(data->env_vars);
	if (!data->paths)
		return (write(2, "Couldn't get paths", 19), 2);
	
	
	data->cmd1.str = ft_parse(data->argV[2]);
	if (!data->cmd1.str)
		return (free_fields(data), write(2, "Parse error cmd1\n", 19), 2);
	i = 0;
	while (*(data->cmd1.str + i))
		ft_printf("%s\n", *(data->cmd1.str + i++));
	ft_printf("\n");

	data->cmd2.str = ft_parse(data->argV[3]);
	if (!data->cmd2.str)
		return (free_fields(data), write(2, "Parse error cmd2\n", 19), 2);
	i = 0;
	while (*(data->cmd2.str + i))
		ft_printf("%s\n", *(data->cmd2.str + i++));
	ft_printf("\n");
	ft_printf("\n");
	
	
	data->bin_path1 = get_binary_path(data->cmd1.str[0], data->paths);
	if (!data->bin_path1)
		return (free_fields(data), write(2, "Couldn't get path1\n", 19), 2);
		// return (free_fields(data), perror("Command not found"), 3);
	ft_printf("%s\n", (data->bin_path1));
	
	data->bin_path2 = get_binary_path(data->cmd2.str[0], data->paths);
	if (!data->bin_path2)
		return (free_fields(data), write(2, "Couldn't get path2\n", 19), 2);
		// return (free_fields(data), perror("Command not found"), 3);
	ft_printf("%s\n", (data->bin_path2));
	ft_printf("\n");
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

char	*get_binary_path(char *cmd, char **paths)
{
	char	*bin;

	if (access(cmd, F_OK) == 0)
	{
		bin = cmd;
		return (bin);
	}
	while (*paths)
	{
		bin = ft_strjoin(*paths, "/");
		if (!bin)
			return (NULL);
		bin = ft_strjoin(bin, cmd);	// Possible memory leaks here due to change of pointers from previous allocation
		if (!bin)
			return (NULL);
		if (access(bin, F_OK) == 0)
			return (bin);
		paths++;
	}
	return (NULL);
}
