/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:20:42 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/09 23:41:53 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	t_input	ag;

	if (argc != 5)
		return (write(2, "Usage: ./pipex infl cmd1 cmd2 outfl\n", 40), 1);
	data.infl = open(argv[1], O_RDONLY);
	if (data.infl == -1)
		ft_fprintf(2, "pipex: input: %s\n", strerror(errno));
	data.outfl = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data.outfl == -1)
	{
		ft_fprintf(2, "pipex: output: %s\n", strerror(errno));
		close(data.infl);
		exit(EXIT_FAILURE);
	}
	initialize_fields(&data);
	ag.agc = argc;
	ag.agv = argv;
	ag.env_vars = envp;
	data.exit_code = get_binaries(&ag, &data);
	if (data.exit_code != 0)
		return (free_fields(&data), data.exit_code);
	if (pipe(data.pipe_fd) != 0)
		return (perror("Pipe error"), free_fields(&data), 1);
	return (data.exit_code = initiate_children(&ag, &data), data.exit_code);
}
