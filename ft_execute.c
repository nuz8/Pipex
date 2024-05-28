/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:35:14 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/28 04:37:09 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
// #include <stdio.h>
#include "pipex.h"

extern char **environ;

// Function to execute a shell command
int main(int argc, char **argv)
{
	// char	*argv[] = {"/bin/ls", "-l", NULL};
	char	*path;
	char	**envp;
	
	if (argc != 2)
	{
		ft_printf("Usage: %s <command>\n", argv[0]);
		return (1);
	}
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
	execve("/bin/ls", (char *[]){"ls", NULL}, environ);
	ft_printf("Error: This should not be printed...\n");	
	return (0);
}