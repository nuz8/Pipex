/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:20:58 by pamatya           #+#    #+#             */
/*   Updated: 2024/04/30 17:01:12 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putchr(unsigned char c)
{
	int	printed;

	printed = 0;
	printed = write(1, &c, 1);
	return (printed);
}

int	ft_putstr(char *str)
{
	int		ec;
	int		printed;

	printed = 0;
	if (!str)
		return (printed = write(1, "(null)", 6), printed);
	while (*str)
	{
		ec = write(1, str++, 1);
		if (ec == -1)
			return (-1);
		printed += ec;
	}
	return (printed);
}
