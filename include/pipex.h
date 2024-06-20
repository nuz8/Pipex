/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:31:21 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/18 16:55:10 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/includes/libft.h"

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

// main.c
// int		main(int argc, char **argv, char **envp);

// pipex.c
void	ft_close(int fd[2]);
void	ft_free_2D(char **memory);
char	**get_paths(char **envp);
char	*get_binary_path(char *cmd, char **paths);

// ft_split2.c
char	**ft_split2(char const *s, char c);

#endif