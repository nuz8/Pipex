/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:31:00 by pamatya           #+#    #+#             */
/*   Updated: 2024/03/27 19:04:54 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t buffer)
{
	char	*d;
	size_t	len;

	len = ft_strlen(dest);
	if (len > buffer)
		return (ft_strlen(src) + buffer);
	d = dest + len;
	buffer -= len;
	return ((len + ft_strlcpy(d, src, buffer)));
}
