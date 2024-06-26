/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:20:42 by pamatya           #+#    #+#             */
/*   Updated: 2024/06/27 01:45:37 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		ret_value;

	if (argc != 5)
		return (write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40), 1);
	nullify_fields(&data);
	data.argC = argc;
	data.argV = argv;
	data.env_vars = envp;
	ret_value = 0;
	ret_value = initiate_commands(&data);
	if (ret_value != 0)
		return (ret_value);
	if (pipe(data.pipe_fd) == -1)
		return (perror("Pipe error"), free_fields(&data), -1);
	ret_value = initiate_children(&data);
	if (ret_value != 0)
		return (free_fields(&data), ret_value);
	return (free_fields(&data), 0);
}
