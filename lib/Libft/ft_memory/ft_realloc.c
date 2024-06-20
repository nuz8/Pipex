/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:03:40 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/20 15:13:34 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Function to mimic the realloc function utilizing the ft_memmove function
void	*ft_realloc(void *ptr, size_t size)
{
	unsigned char	*new_ptr;

	new_ptr = malloc(size + 1);
	if (!new_ptr)
		return (NULL);
	ft_memmove(new_ptr, ptr, size);
	new_ptr[size] = '\0';
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
// 	new_ptr = malloc(size + 1);
// 	if (!new_ptr)
// 		return (NULL);
// 	new_ptr_cpy = new_ptr;
// 	while (size--)
// 		*new_ptr++ = *ptr_cpy++;
// 	*new_ptr = '\0';
// 	free(ptr);
// 	ptr = new_ptr_cpy;
// 	return (ptr);
// }
