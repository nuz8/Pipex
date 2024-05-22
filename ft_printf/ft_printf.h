/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:21:10 by pamatya           #+#    #+#             */
/*   Updated: 2024/04/30 17:03:58 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "./Libft/libft.h"

int		ft_printf(const char *str, ...);
int		ft_putchr(unsigned char c);
int		ft_putstr(char *str);
int		ft_putdec(long num);
int		ft_puthex(unsigned int hexnum, char opt);
int		ft_putptr(void *address);
void	ft_revstr(char *str);
void	ft_strtoup(char *str);
void	ft_basetostr(long num_arg, char *str, long base);
int		ft_intlen(long n, int base);
int		ft_lulen(unsigned long n, int base);

#endif
