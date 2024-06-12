/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:35:14 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/29 00:34:23 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
// #include <stdio.h>
#include "pipex.h"

extern char **environ;

// Function to execute a shell command
int main(void)
{
	// char	*argv[] = {"/bin/ls", "-l", NULL};
	char	*path;
	char	**envp;
	int		fd[2];
	
	pipe(fd);
	fd[0] = open("next_file.txt", O_RDONLY);
	ft_printf("fd[0]: %d\n", fd[0]);
	dup2(fd[0], STDIN_FILENO);
	ft_printf("fd[1]: %d\n", fd[1]);
	close(fd[0]);
	close(fd[1]);
	
	// if (argc != 2)
	// {
	// 	ft_printf("Usage: %s <command>\n", argv[0]);
	// 	return (1);
	// }
	path = getenv("PATH");
	// ft_printf("PATH: %s\n", path);
	
	envp = ft_split(path, ':');
	// while (*envp)
	// {
	// 	ft_printf("%s\n", *envp);
	// 	envp++;
	// }
	
	
	// Execute the command "ls -l"
	// execve("/bin/ls", (char *[]){"ls", "-la", NULL}, envp);
	execve("/usr/bin/grep", (char *[]){"grep", "fork", NULL}, environ);
	ft_printf("Error: This should not be printed...\n");	
	return (0);
}