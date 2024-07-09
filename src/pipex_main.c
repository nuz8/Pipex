/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:20:42 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/09 04:47:43 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	t_pipex	data;
// 	int		exit;
// 	// int		i;

// 	// ft_printf("Total no. of args:	%d\n", argc);
// 	// i = 0;
// 	// while (i < argc)
// 	// 	ft_printf(">>%s<<\n", argv[i++]);

// 	if (argc != 5)
// 		return (write(2, "Usage: ./pipex infl cmd1 cmd2 outfl\n", 40), 1);
// 	exit = 0;
// 	initialize_fields(&data);
// 	ag.argC = argc;
// 	ag.argV = argv;
// 	ag.env_vars = envp;
// 	exit = get_binaries(&data);
// 	if (exit != 0)
// 		return (exit);
// 	if (pipe(data.pipe_fd) == -1)
// 		return (perror("Pipe error"), free_fields(&data), -1);
// 	exit = initiate_children(&data);
// 	if (exit != 0)
// 		return (free_fields(&data), exit);
// 	return (free_fields(&data), 0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_pipex	*data;
// 	int		exit_val;

// 	if (argc != 5)
// 		return (write(2, "Usage: ./pipex infl cmd1 cmd2 outfl\n", 40), 1);
// 	data = malloc(1 * sizeof(t_pipex));
// 	if ((data->infl = open(argv[1], O_RDONLY)) == -1)
// 	{
// 		// perror("infl:");
// 		ft_fprintf(2, "pipex: input: %s\n", strerror(errno));
// 	}
// 	if ((data->outfl = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
// 	{
// 		// perror("outfl:");
// 		ft_fprintf(2, "pipex: output: %s\n", strerror(errno));
// 		close(data->infl);
// 		exit(EXIT_FAILURE);
// 	}
// 	exit_val = 0;
// 	initialize_fields(data);
// 	ag->argC = argc;
// 	ag->argV = argv;
// 	ag->env_vars = envp;
// 	exit_val = get_binaries(data);
// 	if (exit_val != 0)
// 		return (exit_val);
// 	if ((exit_val = pipe(data->pipe_fd)) != 0)
// 		return (perror("Pipe error"), free_fields(data), exit_val);
// 	exit_val = initiate_children(data);

// 	// return (free_fields(data), exit_val);
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	t_input	ag;

	if (argc != 5)
		return (write(2, "Usage: ./pipex infl cmd1 cmd2 outfl\n", 40), 1);
	if ((data.infl = open(argv[1], O_RDONLY)) == -1)
		ft_fprintf(2, "pipex: input: %s\n", strerror(errno));
	if ((data.outfl = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
	{
		ft_fprintf(2, "pipex: output: %s\n", strerror(errno));
		close(data.infl);
		exit(EXIT_FAILURE);
	}
	initialize_fields(&data);
	ag.argC = argc;
	ag.argV = argv;
	ag.env_vars = envp;
	data.exit_code = get_binaries(&ag, &data);
	if (data.exit_code != 0)
		return (free_fields(&data), data.exit_code);
	if (pipe(data.pipe_fd) != 0)
		return (perror("Pipe error"), free_fields(&data), 1);
	data.exit_code = initiate_children(&ag, &data);
	return (data.exit_code);
}
