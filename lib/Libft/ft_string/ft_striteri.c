/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:54:51 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/01 13:06:29 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	// unsigned int	len;

	if (!s || !f)
		return ;
	// len = ft_strlen(s);
	i = 0;
	while (s[i])
	{
		f(i, &(s[i]));
		i++;
	}
}
