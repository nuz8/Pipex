/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:10:03 by pamatya           #+#    #+#             */
/*   Updated: 2024/03/27 19:05:57 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*f_findp(char const *start, char const *set, int const direction)
{
	char	*found;
	char	*check;

	found = (char *)start;
	check = (char *)set;
	while (*check && *found)
	{
		while (*check)
		{
			if (*found == *check)
			{
				found += direction;
				break ;
			}
			else
				check++;
		}
		if (*check != '\0')
			check = (char *)set;
	}
	return (found);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	char	*startp;
	char	*endp;
	size_t	len;

	if (!s1)
		return (NULL);
	if (!*s1)
		return ((char *)ft_calloc(1, sizeof(char)));
	startp = f_findp(s1, set, 1);
	endp = f_findp((s1 + ft_strlen(s1) - 1), set, -1);
	if (!*startp)
		endp = startp;
	len = endp - startp + 1;
	if (len < 0)
		len = 0;
	trimmed = (char *)malloc((len + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	len = 0;
	while (startp <= endp)
		*(trimmed + len++) = *startp++;
	*(trimmed + len) = '\0';
	return (trimmed);
}
