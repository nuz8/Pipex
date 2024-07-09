/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:31:21 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/09 23:32:09 by pamatya          ###   ########.fr       */
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

typedef struct s_input
{
	int			agc;
	char		**agv;
	char		**env_vars;
}				t_input;

typedef struct s_str_list
{
	char				**str;
	struct s_str_list	*next;
}				t_str_list;

typedef struct s_pipex
{
	char		**paths;
	int			infl;
	int			outfl;
	t_str_list	cmd1;
	t_str_list	cmd2;
	char		*bin_path1;
	char		*bin_path2;
	int			pipe_fd[2];
	int			exit_code;
}				t_pipex;

// pipex_main.c
// int		main(int argc, char **argv, char **envp);

// binaries.c
int		get_binaries(t_input *ag, t_pipex *data);
char	**get_paths(char **envp);
void	get_commands(t_input *ag, t_pipex *data);
char	*get_binary_path(t_str_list *cmd, char **paths);
int		remove_path(t_str_list *cmd);

// parsing.c
char	**ft_parse(char const *s);
size_t	f_word_count(char const *str);
size_t	f_word_len(char const *str, char stop);
int		f_alloc_words(char **parsed, char const *s);

// children.c
int		initiate_children(t_input *ag, t_pipex *data);
void	child_read(t_input *ag, t_pipex *data);
void	child_write(t_input *ag, t_pipex *data);

// utilities.c
void	initialize_fields(t_pipex *data);
void	free_fields(t_pipex *data);
void	ft_close_pipe(int fd[]);
void	free_exit(t_pipex *data, int ec);
void	close_free_exit(char *str, t_pipex *data, int ec);

#endif
