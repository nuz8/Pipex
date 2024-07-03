/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:20:42 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/03 02:01:04 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		ret_value;
	// int		i;

	// ft_printf("Total no. of args:	%d\n", argc);
	// i = 0;
	// while (i < argc)
	// 	ft_printf(">>%s<<\n", argv[i++]);

	if (argc != 5)
		return (write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40), 1);
	initialize_fields(&data);
	data.argC = argc;
	data.argV = argv;
	data.env_vars = envp;
	ret_value = 0;
	ret_value = get_binaries(&data);
	if (ret_value != 0)
		return (ret_value);
	if (pipe(data.pipe_fd) == -1)
		return (perror("Pipe error"), free_fields(&data), -1);
	ret_value = initiate_children(&data);
	if (ret_value != 0)
		return (free_fields(&data), ret_value);
	return (free_fields(&data), 0);
}
