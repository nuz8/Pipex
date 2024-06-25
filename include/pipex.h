/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:31:21 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/26 00:03:51 by pamatya          ###   ########.fr       */
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

typedef struct	s_str_list
{
	char				**str;
	struct s_str_list	*next;
}				t_str_list;

typedef struct	s_pipex
{
	int			argC;
	char		**argV;
	char		**env_vars;
	char		**paths;
	int			infile;
	int			outfile;
	t_str_list	cmd1;
	t_str_list	cmd2;
	char		*bin_path1;
	char		*bin_path2;
	int			pipe_fd[2];
}				t_pipex;

// pipex_main.c
// int		main(int argc, char **argv, char **envp);

// pipex_utils.c
void	ft_close(int fd[]);
char	**get_paths(char **envp);
char	*get_binary_path(char *cmd, char **paths);
size_t	param_count(char **cmd);
char	*ft_weave(char *str1, char *str2, char separater);
size_t	ft_weave2(char *str1, char *str2, char separater);
char	**ft_parse_back(char **cmd);

// children.c
int	child_read(t_pipex *data);
int	child_write(t_pipex *data);
int	initiate_children(t_pipex *data);

// fields.c
int	nullify_fields(t_pipex *data);
int	free_fields(t_pipex *data);
int	initiate_commands(t_pipex *data);

// ft_parse.c
char	**ft_parse(char const *s, char c);

#endif
