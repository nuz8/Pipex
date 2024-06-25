/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:07:34 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/26 00:10:22 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	nullify_fields(t_pipex *data);
int	free_fields(t_pipex *data);
int	initiate_commands(t_pipex *data);

int	nullify_fields(t_pipex *data)
{
	data->paths = NULL;
	data->cmd1.str = NULL;
	data->cmd2.str = NULL;
	data->bin_path1 = NULL;
	data->bin_path2 = NULL;
	return (0);
}

int	free_fields(t_pipex *data)
{
	if (data->paths)
		ft_free2D(data->paths);
	if (data->cmd1.str)
		ft_free2D(data->cmd1.str);
	if (data->cmd2.str)
		ft_free2D(data->cmd2.str);
	if (data->bin_path1)
		free(data->bin_path1);
	if (data->bin_path2)
		free(data->bin_path2);
	return (0);
}

int	initiate_commands(t_pipex *data)
{
	data->paths = get_paths(data->env_vars);
	if (!data->paths)
		return (write(2, "Couldn't get paths:", 19), 2);
	data->cmd1.str = ft_split(data->argV[2], ' ');
	if (!data->cmd1.str)
		return (free_fields(data), write(2, "Couldn't split.\n", 19), 2);
	data->bin_path1 = get_binary_path(data->cmd1.str[0], data->paths);
	if (!data->bin_path1)
		return (free_fields(data), write(2, "Couldn't get path1\n", 25), 2);
	data->cmd2.str = ft_split(data->argV[3], ' ');
	if (!data->cmd2.str)
		return (free_fields(data), write(2, "Couldn't split.\n", 19), 2);
	// cmd2 = ft_parse(cmd2);
	data->bin_path2 = get_binary_path(data->cmd2.str[0], data->paths);
	if (!data->bin_path2)
		return (free_fields(data), write(2, "Couldn't get path2\n", 25), 2);
	return (0);
}
