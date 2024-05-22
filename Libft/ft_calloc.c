/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:23:08 by pamatya           #+#    #+#             */
/*   Updated: 2024/03/27 19:01:52 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	char	*wrt;
	size_t	byts;

	byts = count * size;
	ptr = malloc(byts);
	if (!ptr)
		return (NULL);
	wrt = (char *)ptr;
	while (byts--)
		*wrt++ = '\0';
	return (ptr);
}
