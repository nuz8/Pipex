/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:30:19 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/08 04:40:41 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int		initiate_children(t_pipex *data);
void	child_read(t_pipex *data);
void	child_write(t_pipex *data);

// data.pipe_fd[0]	-	read end
// data.pipe_fd[1]	-	write end

int	initiate_children(t_pipex *data)
{
	pid_t	pid[2];
	int		ec1;
	// int		ec[2];
	// int		e[2];

	if ((pid[0] = fork()) == -1)
	{
		perror("Fork1 error");
		ft_close(data->pipe_fd);
		free_fields(data);
		exit(EXIT_FAILURE);
	}
	if (pid[0] == 0)
		child_read(data);
	
	if ((pid[1] = fork()) == -1)
	{
		perror("Fork2 error");
		ft_close(data->pipe_fd);
		free_fields(data);
		exit(EXIT_FAILURE);
	}
	if (pid[1] == 0)
		child_write(data);

	ft_close(data->pipe_fd);
	free_fields(data);
	waitpid(pid[1], &ec1, 0);
	// if (WIFEXITED(ec1))
	// 	exit(WEXITSTATUS(ec1));
	if (WIFEXITED(ec1))
		data->status = WEXITSTATUS(ec1);
	
	// waitpid(pid[0], &(ec[0]), 0);
	// waitpid(pid[1], &(ec[1]), 0);

	// data->status = ((ec[0]) >> 8) & 0x000000ff;
	// if ((((ec[1]) >> 8) & 0x000000ff) != 0)
	// 	data->status = ((ec[1]) >> 8) & 0x000000ff;

	// if (WIFEXITED(ec[0]))
	// 	e[0] = WEXITSTATUS(ec[0]);
	// if (WIFEXITED(ec[1]))
	// 	e[1] = WEXITSTATUS(ec[1]);

	// if (e[0] != 0)
	// 	data->status = e[0];
	// if (e[1] != 0)
	// 	data->status = e[1];
	// else
	// 	data->status = 0;
	return (data->status);
}

// Using this:
// data->status = ((*ec) >> 8) & 0x000000ff;
// Instead of:
// if (WIFEXITED(ec))
// 	data->status = WEXITSTATUS(ec);
// These are doing the same thing

void	child_read(t_pipex *data)
{
	// Child process 1

	close(data->pipe_fd[0]);
	if ((dup2(data->infile, STDIN_FILENO)) == -1)
	{
		// perror("dup2");
		close(data->infile);
		close(data->pipe_fd[1]);
		free_fields(data);
		exit(127);
	}
	if ((dup2(data->pipe_fd[1], STDOUT_FILENO)) == -1)
	{
		// perror("dup2");
		close(data->infile);
		close(data->pipe_fd[1]);
		free_fields(data);
		exit(127);
	}
	close(data->infile);
	close(data->pipe_fd[1]);

	if (execve(data->bin_path1, data->cmd1.str, data->env_vars) == -1)
		ft_fprintf(2, "pipex: %s: command not found\n", data->cmd1.str[0]);
		// perror("pipex: cmd1");
	free_fields(data);
	exit(127);
}

void	child_write(t_pipex *data)
{
	// Child process 2

	close(data->pipe_fd[1]);
	if ((dup2(data->pipe_fd[0], STDIN_FILENO)) == -1)
	{
		perror("dup2");
		close(data->outfile);
		close(data->pipe_fd[0]);
		free_fields(data);
		exit(127);
	}
	if ((dup2(data->outfile, STDOUT_FILENO)) == -1)
	{
		perror("dup2");
		close(data->outfile);
		close(data->pipe_fd[0]);
		free_fields(data);
		exit(127);
	}
	close(data->outfile);
	close(data->pipe_fd[0]);
	
	if (execve(data->bin_path2, data->cmd2.str, data->env_vars) == -1)
		ft_fprintf(2, "pipex: %s: command not found\n", data->cmd2.str[0]);
		// perror("pipex: cmd2");
	free_fields(data);
	exit(127);
}
