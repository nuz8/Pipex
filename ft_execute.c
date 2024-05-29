/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:35:14 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/29 02:50:53 by pamatya          ###   ########.fr       */
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
	// fd[1] = open("next_file.txt", O_WRONLY | O_CREAT, 0777);
	fd[0] = open("next_file.txt", O_RDONLY);
	dup2(fd[0], STDIN_FILENO);
	// dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	
	// if (argc != 2)
	// {
	// 	ft_printf("Usage: %s <command>\n", argv[0]);
	// 	return (1);
	// }
	
	path = getenv("PATH");
	// ft_printf("PATH: %s\n", path);

	while (environ)
	{
		ft_printf("%s\n", *environ);
		environ++;
	}
	
	envp = ft_split(path, ':');
	// while (*envp)
	// {
	// 	ft_printf("%s\n", *envp);
	// 	envp++;
	// }
	
	
	// Execute the command "ls -l"
	// execve("/bin/ls", (char *[]){"ls", "-la", NULL}, envp);
	ft_printf("Executing cat...\n");
	execve("/bin/cat", (char *[]){"cat", NULL}, environ);
	ft_printf("Error: This should not be printed...\n");	
	return (0);
}