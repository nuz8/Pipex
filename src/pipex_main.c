/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:20:42 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/14 15:22:07 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		infile;
	int		outfile;
	int		pid1;
	int		pid2;
	char	**paths;
	char	**cmd1;
	char	**cmd2;
	char	*bin_path1;
	char	*bin_path2;
	// int		i;

	// Check if the number of arguments to be accepted is this
	if (argc != 5)
		return (write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40), 1);
		// return (ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n"), 1);
	
	paths = get_paths(envp);
	if (!paths)
		return (write(2, "Couldn't get paths\n", 19), 2);
	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1)
		return (ft_free_2D(paths) , write(2, "Couldn't split cmd1\n", 19), 2);
	bin_path1 = get_binary_path(cmd1[0], paths);
	if (!bin_path1)
		return (ft_free_2D(paths), ft_free_2D(cmd1), write(2, "Couldn't get binary path\n", 25), 2);
	
	cmd2 = ft_split(argv[3], ' ');
	if (!cmd2)
		return (ft_free_2D(paths), ft_free_2D(cmd1), free(bin_path1), write(2, "Couldn't split cmd2\n", 19), 2);

	bin_path2 = get_binary_path(cmd2[0], paths);
	if (!bin_path2)
		return (ft_free_2D(paths), ft_free_2D(cmd1), free(bin_path1), ft_free_2D(cmd2), write(2, "Couldn't get binary path\n", 25), 2);
	
	// i = 0;
	// while (envp[i])
	// 	ft_printf("%s\n", envp[i++]);
	
	// i = 0;
	// while (paths[i])
	// 	ft_printf("%s\n", paths[i++]);

	// ft_printf("bin_path1: %s\n", bin_path1);
	// ft_printf("bin_path2: %s\n", bin_path2);
	// ft_printf("cmd1[0]: %s\n", cmd1[0]);
	// ft_printf("cmd2[0]: %s\n", cmd2[0]);
	
	pipe(fd);
	// fd[0]	-	read end
	// fd[1]	-	write end
	
	if ((pid1 = fork()) == -1)
		return (write(2, "Couldn't fork\n", 14), ft_close(fd), 3);

	if (pid1 == 0)
	{
		// Child process 1
		// Code for infile with input redirection, and check if it can be opened
		if ((infile = open(argv[1], O_RDONLY)) == -1)
			return (write(2, "Couldn't open infile\n", 21), ft_close(fd), 2);

		// Code for input/output redirection with infile
		close(fd[0]);
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(infile);
		close(fd[1]);

		// execve(argv[2], argv + 2, NULL);
		execve(bin_path1, cmd1, envp);
		ft_printf("The first command executed correctly\n");
	}
	if ((pid2 = fork()) == -1)
		return (write(2, "Couldn't fork\n", 14), ft_close(fd), 3);
	if (pid2 == 0)
	{
		// Child process 2
		// Check if outfile exists, and create it if it doesn't.
		if ((outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			return (write(2, "Couldn't open outfile\n", 22), ft_close(fd), 4);

		// Code for outfile with input/output redirection
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		close(fd[0]);

		// execve(argv[3], argv + 3, NULL);
		execve(bin_path2, cmd2, envp);
	}
	ft_close(fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
