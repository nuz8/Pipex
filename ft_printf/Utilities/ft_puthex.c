/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:20:46 by pamatya           #+#    #+#             */
/*   Updated: 2024/04/30 16:55:59 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_puthex(unsigned int hexnum, char opt)
{
	char	*hex;
	int		printed;
	int		len;

	len = ft_intlen((long)hexnum, 16);
	hex = malloc((len + 1) * sizeof(char));
	if (!hex)
		return (-1);
	ft_basetostr(hexnum, hex, 16);
	if (opt == 'X')
		ft_strtoup(hex);
	printed = ft_putstr(hex);
	free(hex);
	return (printed);
}
