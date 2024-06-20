/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:36:06 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/13 13:06:03 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_form(va_list arg, char opt)
{
	int	printed;

	printed = 0;
	if (opt == 'c')
		printed = ft_putchr((unsigned char)va_arg(arg, int));
	else if (opt == 's')
		printed = ft_putstr(va_arg(arg, char *));
	else if (opt == 'p')
		printed = ft_putptr(va_arg(arg, void *));
	else if (opt == 'd' || opt == 'i')
		printed = ft_putdec(va_arg(arg, int));
	else if (opt == 'u')
		printed = ft_putdec(va_arg(arg, unsigned int));
	else if (opt == 'x' || opt == 'X')
		printed = ft_puthex(va_arg(arg, unsigned int), opt);
	return (printed);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		ec;
	int		printed;

	printed = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str && *str == '%')
				ec = ft_putchr((unsigned char)(*str));
			else
				ec = ft_form(ap, *str);
		}
		else
			ec = ft_putchr((unsigned char)(*str));
		if (ec == -1)
			return (-1);
		else
			printed += ec;
		str++;
	}
	return (va_end(ap), printed);
}
