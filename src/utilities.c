/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:30:53 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/10 02:25:04 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	initialize_fields(t_pipex *data);
void	free_fields(t_pipex *data);
void	ft_close_pipe(int fd[]);
void	free_exit(t_pipex *data, int ec);
void	close_free_exit(char *str, t_pipex *data, int ec);

void	initialize_fields(t_pipex *data)
{
	data->paths = NULL;
	data->cmd1.str = NULL;
	data->cmd1.next = NULL;
	data->cmd2.str = NULL;
	data->cmd2.next = NULL;
	data->bin_path1 = NULL;
	data->bin_path2 = NULL;
	data->exit_code = 0;
}

void	free_fields(t_pipex *data)
{
	if (data->paths)
		ft_free2d_safe(&(data->paths));
	if (data->cmd1.str)
		ft_free2d_safe(&(data->cmd1.str));
	if (data->cmd2.str)
		ft_free2d_safe(&(data->cmd2.str));
	if (data->bin_path1)
		ft_free_safe((void **)&(data->bin_path1));
	if (data->bin_path2)
		ft_free_safe((void **)&(data->bin_path2));
}

void	ft_close_pipe(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}

void	free_exit(t_pipex *data, int ec)
{
	free_fields(data);
	exit(ec);
}

void	close_free_exit(char *str, t_pipex *data, int ec)
{
	perror(str);
	ft_close_pipe(data->pipe_fd);
	free_fields(data);
	exit(ec);
}
