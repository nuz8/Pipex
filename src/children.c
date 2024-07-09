/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:30:19 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/09 23:14:02 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int		initiate_children(t_input *ag, t_pipex *data);
void	child_read(t_input *ag, t_pipex *data);
void	child_write(t_input *ag, t_pipex *data);

int	initiate_children(t_input *ag, t_pipex *data)
{
	pid_t	pid[2];
	int		ec;

	pid[0] = fork();
	if (pid[0] == -1)
		close_free_exit("Fork1 error", data, EXIT_FAILURE);
	if (pid[0] == 0)
		child_read(ag, data);
	pid[1] = fork();
	if (pid[1] == -1)
		close_free_exit("Fork2 error", data, EXIT_FAILURE);
	if (pid[1] == 0)
		child_write(ag, data);
	ft_close_pipe(data->pipe_fd);
	free_fields(data);
	if ((waitpid(pid[1], &ec, 0)) == -1)
		exit(EXIT_FAILURE);
	if (WIFEXITED(ec))
		data->exit_code = WEXITSTATUS(ec);
	return (data->exit_code);
}

void	child_read(t_input *ag, t_pipex *data)
{
	close(data->pipe_fd[0]);
	if ((dup2(data->infl, STDIN_FILENO)) == -1)
	{
		close(data->infl);
		close(data->pipe_fd[1]);
		free_exit(data, 1);
	}
	if ((dup2(data->pipe_fd[1], STDOUT_FILENO)) == -1)
	{
		close(data->infl);
		close(data->pipe_fd[1]);
		free_exit(data, 1);
	}
	close(data->infl);
	close(data->pipe_fd[1]);
	if (execve(data->bin_path1, data->cmd1.str, ag->env_vars) == -1)
		ft_fprintf(2, "pipex: %s: command not found\n", data->cmd1.str[0]);
	free_exit(data, 127);
}

void	child_write(t_input *ag, t_pipex *data)
{
	close(data->pipe_fd[1]);
	if ((dup2(data->pipe_fd[0], STDIN_FILENO)) == -1)
	{
		close(data->outfl);
		close(data->pipe_fd[0]);
		free_exit(data, 1);
	}
	if ((dup2(data->outfl, STDOUT_FILENO)) == -1)
	{
		close(data->outfl);
		close(data->pipe_fd[0]);
		free_exit(data, 1);
	}
	close(data->outfl);
	close(data->pipe_fd[0]);
	if (execve(data->bin_path2, data->cmd2.str, ag->env_vars) == -1)
		ft_fprintf(2, "pipex: %s: command not found\n", data->cmd2.str[0]);
	free_exit(data, 127);
}
