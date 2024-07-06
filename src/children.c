/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:30:19 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/06 22:26:49 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	initiate_children(t_pipex *data);
int	child_read(t_pipex *data);
int	child_write(t_pipex *data);

// data.pipe_fd[0]	-	read end
// data.pipe_fd[1]	-	write end

int	initiate_children(t_pipex *data)
{
	pid_t	pid[2];
	// int		*ec[2];
	int		ec[2];

	// ec[0] = malloc(sizeof(int));
	// ec[1] = malloc(sizeof(int));
	
	if ((pid[0] = fork()) == -1)
	{
		perror("Fork1 error");
		ft_close(data->pipe_fd);
		free_fields(data);
		return (127); //
	}
	if (pid[0] == 0)
		child_read(data);
	
	if ((pid[1] = fork()) == -1)
	{
		perror("Fork2 error");
		ft_close(data->pipe_fd);
		free_fields(data);
		return (127);
	}
	if (pid[1] == 0)
		child_write(data);

	ft_close(data->pipe_fd);
	// waitpid(pid[0], &(data->status), 0);
	waitpid(pid[0], &(ec[0]), 0);
	waitpid(pid[1], &(ec[1]), 0);


	// data->status = ((*ec) >> 8) & 0x000000ff;

	// if ((((ec[0]) >> 8) & 0x000000ff) != 0)
	data->status = ((ec[0]) >> 8) & 0x000000ff;
	// if ((((ec[1]) >> 8) & 0x000000ff) != 0)
	if ((ec[1]) != 0)
		data->status = ((ec[1]) >> 8) & 0x000000ff;

	// return (ec); //

	// data->status = ec[2];
	return (data->status); //
}
// Using this:
// data->status = ((*ec) >> 8) & 0x000000ff;
// Instead of:
// if (WIFEXITED(ec))
// 	data->status = WEXITSTATUS(ec);
// These are equivalent

int	child_read(t_pipex *data)
{
	// Child process 1
	// ft_printf("Child process 1: pid[0] =	%d\n", getpid());

	// Code for infile with input redirection, and check if it can be opened
	if ((data->infile = open(data->argV[1], O_RDONLY)) == -1)
	{
		ft_fprintf(2, "pipex: %s: %s\n", data->argV[1], strerror(errno));
		ft_close(data->pipe_fd);
		free_fields(data);
		return (-333);
	}

	// For input/output redirection with infile
	close(data->pipe_fd[0]);
	dup2(data->infile, STDIN_FILENO);
	dup2(data->pipe_fd[1], STDOUT_FILENO);
	close(data->infile);
	close(data->pipe_fd[1]);

	// Execution of cmd1
	if (execve(data->bin_path1, data->cmd1.str, data->env_vars) == -1)
	{
		ft_fprintf(2, "pipex: %s: command not found\n", data->cmd1.str[0]);
		free_fields(data);
		// exit(127);
	}
	return (-1);
}

int	child_write(t_pipex *data)
{
	// Child process 2
	// ft_printf("Child process 2: pid[1] =	%d\n", getpid());
	
	// Check if outfile exists, if not create it, and truncate before writing.
	if ((data->outfile = open(data->argV[4], O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
	{
		ft_fprintf(2, "pipex: %s: %s\n", data->argV[4], strerror(errno));
		ft_close(data->pipe_fd);
		free_fields(data);
		exit(127);
	}

	// For outfile with input/output redirection
	close(data->pipe_fd[1]);
	dup2(data->pipe_fd[0], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	close(data->outfile);
	close(data->pipe_fd[0]);

	// Execution of cmd2
	if (execve(data->bin_path2, data->cmd2.str, data->env_vars) == -1)
	ft_fprintf(2, "pipex: %s: command not found\n", data->cmd2.str[0]);
	free_fields(data);
	// exit(127);
	return (127);
}
