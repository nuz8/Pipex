/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:20:42 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/25 19:42:53 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	pid_t	pid[2];

	// Check if the number of arguments to be accepted is this
	if (argc != 5)
		return (write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40), 1);
		// return (ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n"), 1);
	
	data.paths = get_paths(envp);
	if (!data.paths)
		return (write(2, "Couldn't get paths\n", 19), 2);
	data.cmd1.str = ft_split(argv[2], ' ');
	if (!data.cmd1.str)
		return (ft_free2D(data.paths) , write(2, "Couldn't split cmd1\n", 19), 2);
	data.bin_path1 = get_binary_path(data.cmd1.str[0], data.paths);
	if (!data.bin_path1)
		return (ft_free2D(data.paths), ft_free2D(data.cmd1.str), write(2, "Couldn't get binary path\n", 25), 2);
	
	// data.cmd2 = malloc(sizeof(t_str_list));
	data.cmd2.str = ft_split(argv[3], ' ');
	if (!data.cmd2.str)
		return (ft_free2D(data.paths), ft_free2D(data.cmd1.str), free(data.bin_path1), write(2, "Couldn't split cmd2\n", 19), 2);

	// cmd2 = ft_parse(cmd2);
	
	data.bin_path2 = get_binary_path(data.cmd2.str[0], data.paths);
	if (!data.bin_path2)
		return (ft_free2D(data.paths), ft_free2D(data.cmd1.str), free(data.bin_path1), ft_free2D(data.cmd2.str), write(2, "Couldn't get binary path\n", 25), 2);
	
	pipe(data.pipe_fd);
	// data.pipe_fd[0]	-	read end
	// data.pipe_fd[1]	-	write end
	
	if ((pid[0] = fork()) == -1)
		return (write(2, "Couldn't fork\n", 14), ft_close(data.pipe_fd), 3);

	if (pid[0] == 0)
	{
		// Child process 1
		// Code for infile with input redirection, and check if it can be opened
		if ((data.infile = open(argv[1], O_RDONLY)) == -1)
			return (write(2, "Couldn't open infile\n", 21), ft_close(data.pipe_fd), 2);

		// Code for input/output redirection with infile
		close(data.pipe_fd[0]);
		dup2(data.infile, STDIN_FILENO);
		dup2(data.pipe_fd[1], STDOUT_FILENO);
		close(data.infile);
		close(data.pipe_fd[1]);

		// execve(argv[2], argv + 2, NULL);
		execve(data.bin_path1, data.cmd1.str, envp);
		ft_printf("The first command executed correctly\n");
	}
	if ((pid[1] = fork()) == -1)
		return (write(2, "Couldn't fork\n", 14), ft_close(data.pipe_fd), 3);
	if (pid[1] == 0)
	{
		// Child process 2
		// Check if outfile exists, and create it if it doesn't.
		if ((data.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			return (write(2, "Couldn't open outfile\n", 22), ft_close(data.pipe_fd), 4);

		// Code for outfile with input/output redirection
		close(data.pipe_fd[1]);
		dup2(data.pipe_fd[0], STDIN_FILENO);
		dup2(data.outfile, STDOUT_FILENO);
		close(data.outfile);
		close(data.pipe_fd[0]);

		// execve(argv[3], argv + 3, NULL);
		execve(data.bin_path2, data.cmd2.str, envp);
	}
	ft_close(data.pipe_fd);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
