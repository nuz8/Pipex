/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_test2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:11:44 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/26 21:03:40 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	int n = sizeof(arr) / sizeof(arr[0]);
	int start, end;
	int fd[2];
	int id;
	int sum;
	int i;
	int sum_child;
	int total_sum;

	if (pipe(fd) == -1)
		return (1);
	id = fork();
	if (id == -1)
		return (2);
	if (id == 0)
	{
		// Child process
		start = 0;
		end = n / 2;
	}
	else
	{
		// Parent process
		start = n / 2;
		end = n;
	}
	
	sum = 0;
	i = start;
	while (i < end)
	{
		sum += arr[i];
		i++;
	}
	printf("Calculated partial sum: %d\n", sum);

	if (id == 0)
	{
		// Child process
		close(fd[0]);
		if (write(fd[1], &sum, sizeof(sum)) == -1)
			return (close(fd[1]), 3);
		close(fd[1]);
	}
	else
	{
		// Parent process
		close(fd[1]);
		if (read(fd[0], &sum_child, sizeof(sum_child)) == -1)
			return (close(fd[0]), 4);
		close(fd[0]);

		total_sum = sum + sum_child;
		printf("Total sum: %d\n", total_sum);
		wait(NULL);
	}
	
	return (0);
}
