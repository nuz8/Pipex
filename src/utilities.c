/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:30:53 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/09 04:08:42 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	initialize_fields(t_pipex *data);
void	free_fields(t_pipex *data);
void	ft_close_pipe(int fd[]);
void	free_exit(t_pipex *data, int ec);
void	close_free_exit(t_pipex *data, int ec);

void	initialize_fields(t_pipex *data)
{
	data->paths = NULL;
	data->cmd1.str = NULL;
	data->cmd2.str = NULL;
	data->bin_path1 = NULL;
	data->bin_path2 = NULL;
	data->exit_code = 0;
}

// Unprotected free function for 1d and 2d char pointers.
// int	free_fields(t_pipex *data)
// {
// 	if (data->paths)
// 		ft_free2d((data->paths));
// 	if (data->cmd1.str)
// 		ft_free2d((data->cmd1.str));
// 	if (data->cmd2.str)
// 		ft_free2d((data->cmd2.str));
// 	if (data->bin_path1)
// 		free((data->bin_path1));
// 	if (data->bin_path2)
// 		free((data->bin_path2));
// 	return (0);
// }

// int	free_fields(t_pipex *data)
// {
// 	if (data->paths)
// 		ft_free2d_safe(&(data->paths));
// 	if (data->cmd1.str)
// 		ft_free2d_safe(&(data->cmd1.str));
// 	if (data->cmd2.str)
// 		ft_free2d_safe(&(data->cmd2.str));
// 	if (data->bin_path1)
// 		ft_free_safe(&(data->bin_path1));
// 	if (data->bin_path2)
// 		ft_free_safe(&(data->bin_path2));
// 	return (0);
// }

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

// int	free_fields(t_pipex *data)
// {
// 	if (data->paths){
// 		ft_printf("Freeing 2d &data->paths at %p\n", &(data->paths));
// 		ft_printf("Freeing 2d data->paths at %p\n", data->paths);
// 		ft_printf("Freeing 2d *data->paths at %p\n\n", *(data->paths));
// 		ft_free2d_safe(&(data->paths));
// 	}
// 	if (data->cmd1.str){
// 		ft_printf("Freeing 2d &data->cmd1.str at %p\n", &(data->cmd1.str));
// 		ft_printf("Freeing 2d data->cmd1.str at %p\n", data->cmd1.str);
// 		ft_printf("Freeing 2d *data->cmd1.str at %p\n\n", *(data->cmd1.str));
// 		ft_free2d_safe(&(data->cmd1.str));
// 	}
// 	if (data->cmd2.str){
// 		ft_printf("Freeing 2d &data->cmd2.str at %p\n", &(data->cmd2.str));
// 		ft_printf("Freeing 2d data->cmd2.str at %p\n", data->cmd2.str);
// 		ft_printf("Freeing 2d *data->cmd2.str at %p\n\n", *(data->cmd2.str));
// 		ft_free2d_safe(&(data->cmd2.str));
// 	}
// 	if (data->bin_path1){
// 		ft_printf("Freeing &data->bin_path1 at %p\n", &(data->bin_path1));
// 		ft_printf("Freeing data->bin_path1 at %p\n\n", data->bin_path1);
// 		ft_free_safe(&(data->bin_path1));
// 	}
// 	if (data->bin_path2){	
// 		ft_printf("Freeing &data->bin_path2 at %p\n", &(data->bin_path2));
// 		ft_printf("Freeing data->bin_path2 at %p\n\n", data->bin_path2);
// 		ft_free_safe(&(data->bin_path2));
// 	}
// 	return (0);
// }

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

void	close_free_exit(t_pipex *data, int ec)
{
	ft_close_pipe(data->pipe_fd);
	free_fields(data);
	exit(ec);
}