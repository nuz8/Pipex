/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_environ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 06:59:24 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/29 07:03:30 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char **environ;

int	main(void)
{
	while (*environ)
	{
		ft_printf("%s\n", *environ);
		environ++;
	}
	return (0);
}