/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lengths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:27:23 by pamatya           #+#    #+#             */
/*   Updated: 2024/04/30 17:00:48 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_intlen(long num, int base)
{
	int	len;

	len = 0;
	if (num <= 0)
		len = 1;
	while (num)
	{
		len++;
		num /= base;
	}
	return (len);
}

int	ft_lulen(unsigned long num, int base)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		len++;
		num /= base;
	}
	return (len);
}
