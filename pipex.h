/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:31:21 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/29 04:55:00 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./Libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <fcntl.h>
// # include <sys/types.h>
// # include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

# include <errno.h>

// # include <sys/types.h>	// Included for umask
// # include <sys/stat.h>	// Included for umask

void	ft_close(int fd[2]);

#endif