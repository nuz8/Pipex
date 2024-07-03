/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 22:19:54 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/03 03:27:37 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_free2d(char **memory)
{
	size_t	i;

	i = 0;
	// ft_printf("Free2d memory (**) at %p\n", memory);
	// ft_printf("Free2d *memory (*) at %p\n\n", *memory);
	while (memory[i] != NULL)
	{
		free(memory[i]);
		memory[i] = NULL;
		i++;
	}
	free(memory);
}

// Important:
// Note that the 1d pointer passed by reference here (**) should also exist by
// reference in the calling function. The correct way to call this function is
// to either call it from the function where the 1d pointer is dyn.ly allocated,
// or from another function which has also received the 1d pointer by reference
// (**) when the 1d pointer was allocated by another function which calls that
// function.
void	ft_free_safe(char **memory)
{
	if ((*memory) == NULL)
		return ;
	else
	{
		// ft_printf("Free_safe memory (**) at %p\n", memory);
		// ft_printf("Free_safe *memory (*) at %p\n\n", *memory);
		free(*memory);
		(*memory) = NULL;
	}
}

// Important:
// Note that the 2d pointer passed by reference here (***) should also exist by
// reference in the calling function. The correct way to call this function is
// to either call it from the function where the 2d pointer is dyn.ly allocated,
// or from another function which has also received the 2d pointer by reference
// (***) when the 2d pointer was allocated by another function which calls that
// function.
void	ft_free2d_safe(char ***memory)
{
	size_t	i;

	if ((*memory) == NULL)
		return ;
	i = 0;
	// ft_printf("Free2dsafe memory (***) at %p\n", memory);
	// ft_printf("Free2dsafe *memory (**) at %p\n\n", *memory);
	while ((*memory) && (*memory)[i] != NULL)
	{
		free((*memory)[i]);
		(*memory)[i] = NULL;
		i++;
	}
	if ((*memory) != NULL)
	{
		free((*memory));
		(*memory) = NULL;
	}
}
