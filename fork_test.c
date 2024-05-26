/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:11:44 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/26 22:19:14 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int	main(int argc, char *argv[])
{
	int id = fork();
	int id2;
	int id3;
	int n;
	int i;
	
	if (id == 0)
	{
		printf("Child process\n");
		id2 = fork();
		if (id2 == 0)
		{
			printf("Grandchild process\n");
			id3 = fork();
			if (id3 == 0)
			{
				printf("Great-grandchild process\n");
				n = 1;
			}
			else
			{
				printf("Grandchild process\n");
				n = 6;
			}
			// if (id3 != 0)
			// 	wait(NULL);
		}
		else
		{
			printf("Child process\n");
			n = 11;
		}
		// if (id2 != 0)
		// 	wait(NULL);
	}
	else
	{
		printf("Parent process\n");
		n = 16;
	}
	if (id != 0 || id2 != 0 || id3 != 0)
		wait(NULL);
	i = n;
	while (i < n + 5)
	{
		usleep(100000); // 100000 microseconds = 0.1 seconds
		printf("%d\n", i++);
		fflush(stdout);
	}
	if (id != 0)
		printf("\n");
	
	return (0);
}
