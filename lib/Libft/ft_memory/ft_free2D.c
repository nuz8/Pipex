/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 22:19:54 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/28 00:35:53 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_free2d(char **memory)
{
	size_t	i;

	i = 0;
	while (memory[i] != NULL)
		free(memory[i++]);
	free(memory);
}
