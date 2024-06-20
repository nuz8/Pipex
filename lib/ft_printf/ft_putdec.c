/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:20:52 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/13 13:05:25 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putdec(long num)
{
	char	*str;
	int		n_len;
	int		printed;

	printed = 0;
	n_len = ft_intlen(num, 10);
	str = (char *)malloc((n_len + 1) * sizeof(char));
	if (!str)
		return (-1);
	ft_basetostr(num, str, 10);
	printed = ft_putstr(str);
	free(str);
	return (printed);
}
