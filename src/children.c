/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:30:19 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/28 00:39:09 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	child_read(t_pipex *data);
int	child_write(t_pipex *data);
int	initiate_children(t_pipex *data);

// data.pipe_fd[0]	-	read end
// data.pipe_fd[1]	-	write end

int	child_read(t_pipex *data)
{
	// Child process 1
	// Code for infile with input redirection, and check if it can be opened
	if ((data->infile = open(data->argV[1], O_RDONLY)) == -1)
		return (perror("Infile error"), ft_close(data->pipe_fd), 3);

	// Code for input/output redirection with infile
	close(data->pipe_fd[0]);
	dup2(data->infile, STDIN_FILENO);
	dup2(data->pipe_fd[1], STDOUT_FILENO);
	close(data->infile);
	close(data->pipe_fd[1]);

	// execve(argv[2], argv + 2, NULL);
	execve(data->bin_path1, data->cmd1.str, data->env_vars);
	ft_printf("1st command failed.\n");
	return (1);
}

int	child_write(t_pipex *data)
{
	// Child process 2
	// Check if outfile exists, and create it if it doesn't.
	if ((data->outfile = open(data->argV[4], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		return (perror("Outfile error"), ft_close(data->pipe_fd), 4);

	// Code for outfile with input/output redirection
	close(data->pipe_fd[1]);
	dup2(data->pipe_fd[0], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	close(data->outfile);
	close(data->pipe_fd[0]);

	// execve(argv[3], argv + 3, NULL);
	execve(data->bin_path2, data->cmd2.str, data->env_vars);
	ft_printf("2nd command failed.\n");
	return (1);
}

int	initiate_children(t_pipex *data)
{
	pid_t	pid[2];

	if ((pid[0] = fork()) == -1)
		return (perror("Fork1 error"), ft_close(data->pipe_fd), 2);
	if (pid[0] == 0)
		child_read(data);	
	if ((pid[1] = fork()) == -1)
		return (perror("Fork2 error"), ft_close(data->pipe_fd), 2);
	if (pid[1] == 0)
		child_write(data);
	ft_close(data->pipe_fd);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
