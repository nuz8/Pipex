/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:50:44 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/20 20:20:17 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// #include "../include/pipex.h"

// Function to mimic the realloc function utilizing the ft_memmove function
void	*ft_realloc(void *ptr, size_t size)
{
	unsigned char	*new_ptr;

	if (size == 0 && ptr)
		size = 1;
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
		memmove(new_ptr, ptr, size);
	free(ptr);
	ptr = new_ptr;
	return (ptr);
}

// // Function to mimic the realloc function without utilizing ft_memmove
// void	*ft_realloc(void *ptr, size_t size)
// {
// 	unsigned char	*ptr_cpy;
// 	unsigned char	*new_ptr;
// 	unsigned char	*new_ptr_cpy;

// 	ptr_cpy = (unsigned char *)ptr;
// 	if (size == 0 && ptr)
// 		size = 1;
// 	new_ptr = malloc(size);
// 	if (!new_ptr)
// 		return (NULL);
// 	new_ptr_cpy = new_ptr;
// 	if (ptr)
// 	{
// 		while (size--)
// 			*new_ptr++ = *ptr_cpy++;
// 	}
// 	free(ptr);
// 	ptr = new_ptr_cpy;
// 	return (ptr);
// }

// Main for random string testing and comparing with standard library function.
int	main(void)
{
	char	*str1;
	char	*str2;
	int		n;

	str1 = strdup("This is the only text that should be read very carefullly.");
	str2 = strdup("This is definitely not the only text that should be read very carefullly.");
	
	n = printf("%s\n", str1);
	printf("Printed = %d\n", n);
	write(1, str1, 100);
	write(1, "\n", 1);
	n = printf("Initial addr:			%p\n", str1);
	
	str1 = ft_realloc(str1, 15 * sizeof(char));
	str1[14] = '\0';
	n = printf("%s\n", str1);
	printf("Printed = %d\n", n);
	write(1, str1, 100);
	write(1, "\n", 1);
	n = printf("ft_realloc 15 addr:		%p\n", str1);
	
	str1 = ft_realloc(str1, 10 * sizeof(char));
	str1[9] = '\0';
	n = printf("%s\n", str1);
	printf("Printed = %d\n", n);
	write(1, str1, 100);
	write(1, "\n", 1);
	n = printf("ft_realloc 10 addr:		%p\n", str1);

	str1 = ft_realloc(str1, 6 * sizeof(char));
	str1[5] = '\0';
	n = printf("%s\n", str1);
	printf("Printed = %d\n", n);
	write(1, str1, 100);
	write(1, "\n", 1);
	n = printf("ft_realloc 6 addr:		%p\n", str1);
	
	n = printf("\n");
	write(1, "\n", 1);
	
	n = printf("%s\n", str2);
	printf("Printed = %d\n", n);
	write(1, str2, 100);
	write(1, "\n", 1);
	n = printf("Initial addr:			%p\n", str2);
	
	str2 = realloc(str2, 15 * sizeof(char));
	str2[14] = '\0';
	n = printf("%s\n", str2);
	printf("Printed = %d\n", n);
	write(1, str2, 100);
	write(1, "\n", 1);
	n = printf("Realloc 15 addr:		%p\n", str2);
	
	str2 = realloc(str2, 10 * sizeof(char));
	str2[9] = '\0';
	n = printf("%s\n", str2);
	printf("Printed = %d\n", n);
	write(1, str2, 100);
	write(1, "\n", 1);
	n = printf("Realloc 10 addr:		%p\n", str2);
	
	str2 = realloc(str2, 6 * sizeof(char));
	str2[5] = '\0';
	n = printf("%s\n", str2);
	printf("Printed = %d\n", n);
	write(1, str2, 100);
	write(1, "\n", 1);
	n = printf("Realloc 6 addr:			%p\n", str2);
	
	n = printf("\n");
	write(1, "\n", 1);
	
	free(str1);
	free(str2);
	return (0);
}




// // Main for testing from small string to very large reallocation and coompare the old and new addresses
// int	main(void)
// {
// 	char	*str1;
// 	char	*str2;
// 	int		n;

// 	str1 = strdup("AB");
// 	str2 = strdup("C");
	
// 	n = printf("%s\n", str1);
// 	printf("Printed = %d\n", n);
// 	write(1, str1, 100);
// 	write(1, "\n", 1);
// 	n = printf("Initial addr:			%p\n", str1);
	
// 	str1 = ft_realloc(str1, 90 * sizeof(char));
// 	n = printf("%s\n", str1);
// 	printf("Printed = %d\n", n);
// 	write(1, str1, 100);
// 	write(1, "\n", 1);
// 	n = printf("ft_realloc 90 addr:		%p\n", str1);

// 	str1 = ft_realloc(str1, 20 * sizeof(char));
// 	n = printf("%s\n", str1);
// 	printf("Printed = %d\n", n);
// 	write(1, str1, 100);
// 	write(1, "\n", 1);
// 	n = printf("ft_realloc 20 addr:		%p\n", str1);

// 	str1 = ft_realloc(str1, 95 * sizeof(char));
// 	n = printf("%s\n", str1);
// 	printf("Printed = %d\n", n);
// 	write(1, str1, 100);
// 	write(1, "\n", 1);
// 	n = printf("ft_realloc 95 addr:		%p\n", str1);

// 	n = printf("\n");
// 	write(1, "\n", 1);
	
// 	n = printf("%s\n", str2);
// 	printf("Printed = %d\n", n);
// 	write(1, str2, 100);
// 	write(1, "\n", 1);
// 	n = printf("Initial addr:			%p\n", str2);
	
// 	str2 = realloc(str2, 90 * sizeof(char));
// 	n = printf("%s\n", str2);
// 	printf("Printed = %d\n", n);
// 	write(1, str2, 100);
// 	write(1, "\n", 1);
// 	n = printf("Realloc 90 addr:		%p\n", str2);

// 	str2 = realloc(str2, 20 * sizeof(char));
// 	n = printf("%s\n", str2);
// 	printf("Printed = %d\n", n);
// 	write(1, str2, 100);
// 	write(1, "\n", 1);
// 	n = printf("Realloc 20 addr:		%p\n", str2);

// 	str2 = realloc(str2, 95 * sizeof(char));
// 	n = printf("%s\n", str2);
// 	printf("Printed = %d\n", n);
// 	write(1, str2, 100);
// 	write(1, "\n", 1);
// 	n = printf("Realloc 95 addr:		%p\n", str2);

// 	n = printf("\n");
// 	write(1, "\n", 1);
	
// 	free(str1);
// 	free(str2);
// 	return (0);
// }