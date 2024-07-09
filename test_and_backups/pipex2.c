/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:30:53 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/08 22:41:20 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_close_pipe(int fd[2]);

void	ft_close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int	main(void)
{
	int		fd[2];
	int		infl;
	int		outfl;
	int		pid1;
	int		pid2;
	// char	*envp;
	
	// Check if the number of arguments to be accepted is this
	// if (argc != 5)
	// 	return (write(2, "Invalid no. of arg.s\n", 21), 1);
	
	pipe(fd);
	// fd[0] is the read end of the pipe
	// fd[1] is the write end of the pipe
	
	if ((pid1 = fork()) == -1)
		return (write(2, "Couldn't fork\n", 14), ft_close_pipe(fd), 3);
	if (pid1 == 0)
	{
		// Child process 1
		// Code for infl with input redirection, and check if it can be opened
		// if ((infl = open(argv[1], O_RDONLY)) == -1)
		// 	return (write(2, "Couldn't open infl\n", 21), ft_close_pipe(fd), 2);

		// Code for infl and check if it can be opened
		if ((infl = open("./io_files/infl.txt", O_RDONLY)) == -1)
			return (write(2, "Couldn't open infl\n", 21), ft_close_pipe(fd), 2);
		
		// Code for input/output redirection with infl
		close(fd[0]);
		dup2(infl, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(infl);
		close(fd[1]);
		
		// execve(argv[2], argv + 2, NULL);
		// execve("/bin/cat", (char *[]){"cat", NULL}, NULL);
		execve("/usr/bin/who", (char *[]){"who", NULL}, NULL);
	}
	if ((pid2 = fork()) == -1)
		return (write(2, "Couldn't fork\n", 14), ft_close_pipe(fd), 3);
	if (pid2 == 0)
	{
		// Child process 2
		// Check if outfl exists, and create it if it doesn't.
		// if ((outfl = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)	// Check what the last flag does and what the permissions are
		// 	return (write(2, "Couldn't open outfl\n", 22), ft_close_pipe(fd), 4);

		// if ((outfl = open("outfl.txt", O_WRONLY | O_CREAT, 0777)) == -1)
		if ((outfl = open("./io_files/outfl.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)	// Check what the last flag does and what the permissions are
			return (write(2, "Couldn't open outfl\n", 22), ft_close_pipe(fd), 4);
		
		// Code for outfl with input/output redirection
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(outfl, STDOUT_FILENO);
		close(outfl);
		close(fd[0]);

		// waitpid(pid1, NULL, 0);	// Check why this is needed even though the program seems to work without it

		// execve(argv[3], argv + 3, NULL);
		// execve("/usr/bin/grep", (char *[]){"grep", "-v", "exec", NULL}, NULL);
		execve("/usr/bin/awk", (char *[]){"awk", "$2 == \"console\" {print $3 \" \" $4 \" \" $5}", NULL}, NULL);
	}
	ft_close_pipe(fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
