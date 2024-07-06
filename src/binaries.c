/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:07:34 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/06 17:42:23 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int		get_binaries(t_pipex *data);
char	**get_paths(char **envp);

// int		get_cmdlen(char *cmd_with_path);
// char	*remove_path(char *cmd_with_path);
int		remove_path(t_str_list *cmd);

// int		get_binary_path(t_str_list *cmd, char **paths, char **binary_path);
char	*get_binary_path(t_str_list *cmd, char **paths);
// char	*get_binary_path(char *cmd, char **paths);

int	get_binaries(t_pipex *data)
{
	data->paths = get_paths(data->env_vars);
	if (!data->paths)
	{
		perror("Couldn't get paths");
		free_fields(data);
		exit(127);
	}
		// return (perror("Couldn't get paths"), 2);

	data->cmd1.str = ft_parse(data->argV[2]);
	if (!data->cmd1.str)
	{
		// free_fields(data);
		perror("Parse error cmd1");
		exit(127);
	}

	data->cmd2.str = ft_parse(data->argV[3]);
	if (!data->cmd2.str)
	{
		free_fields(data);
		perror("Parse error cmd2");
		exit (127);
	}

	// data->bin_path1 = get_binary_path((data->cmd1.str[0]), data->paths);
	data->bin_path1 = get_binary_path(&(data->cmd1), data->paths);
	// if (!data->bin_path1)
	// 	ft_fprintf(2, "pipex: %s: command not found\n", data->cmd1.str[0]);
	// ec = get_binary_path(&(data->cmd1), data->paths, &(data->bin_path1));
	
	// data->bin_path2 = get_binary_path((data->cmd2.str[0]), data->paths);
	if (!(data->bin_path2 = get_binary_path(&(data->cmd2), data->paths)))
		return(free_fields(data), 127);
	// if (!(ec = get_binary_path(&(data->cmd2), data->paths, &(data->bin_path2))))
	// {
	// 	// ft_fprintf(2, "pipex: %s: command not found\n", data->cmd2.str[0]);
	// 	free_fields(data);
	// 	return(127);
	// }

	if (remove_path(&(data->cmd1)) == -1)
		return (perror("Remove_path-malloc failed"), -1);
	if (remove_path(&(data->cmd2)) == -1)
		return (perror("Remove_path-malloc failed"), -1);

	return (0);
}

// int	get_binaries(t_pipex *data)
// {
// 	int		i;
	
// 	data->paths = get_paths(data->env_vars);
// 	if (!data->paths)
// 		return (perror("Couldn't get paths"), 2);
	
// 	data->cmd1.str = ft_parse(data->argV[2]);
// 	if (!data->cmd1.str)
// 		return (free_fields(data), perror("Parse error cmd1"), 2);
// 	i = 0;
// 	while (*(data->cmd1.str + i))
// 		ft_printf(">>%s<<\n", *(data->cmd1.str + i++));
// 	ft_printf("\n");

// 	data->cmd2.str = ft_parse(data->argV[3]);
// 	if (!data->cmd2.str)
// 		return (free_fields(data), perror("Parse error cmd1"), 2);
// 	i = 0;
// 	while (*(data->cmd2.str + i))
// 		ft_printf(">>%s<<\n", *(data->cmd2.str + i++));
// 	ft_printf("\n");
// 	ft_printf("\n");

// 	// data->bin_path1 = get_binary_path((data->cmd1.str[0]), data->paths);
// 	data->bin_path1 = get_binary_path(&(data->cmd1), data->paths);
// 	if (!data->bin_path1)
// 		return (free_fields(data), perror("Couldn't get path1"), 2);
// 		// return (free_fields(data), perror("Command not found"), 3);
// 	ft_printf(">>%s<<\n", (data->bin_path1));
	
// 	// data->bin_path2 = get_binary_path((data->cmd2.str[0]), data->paths);
// 	data->bin_path2 = get_binary_path(&(data->cmd2), data->paths);
// 	if (!data->bin_path2)
// 		return (free_fields(data), perror("Couldn't get path2"), 2);
// 		// return (free_fields(data), perror("Command not found"), 3);
// 	ft_printf(">>%s<<\n", (data->bin_path2));
// 	ft_printf("\n");
// 	ft_printf("I am here\n");

// 	i = 0;
// 	while (*(data->cmd1.str + i))
// 	{
// 		ft_printf(">>%s<<\t", *(data->cmd1.str + i++));
// 	}
// 	ft_printf("\n");
// 	ft_printf("I am here as of now\n");
// 	i = 0;
// 	while (*(data->cmd2.str + i))
// 		ft_printf(">>%s<<\n", *(data->cmd2.str + i++));
// 	ft_printf("\n");
// 	ft_printf("\n");
// 	ft_printf("I am here now\n");
	
// 	return (0);
// }

char	**get_paths(char **envp)
{
	char	**paths;
	char	*path;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path = ft_strdup(*envp + 5);
			if (!path)
				return (NULL);
			break ;
		}
		envp++;
	}
	paths = ft_split(path, ':');
	if (!paths)
		return (free(path), NULL);
	return (free(path), paths);
}

// int	remove_path(t_str_list *cmd)
// {
// 	char	*cmd_with_path;
// 	char	*cmd_wo_path;
// 	int		cmd_len;
// 	int		cmdwpath_len;
// 	int		i;

// 	cmd_with_path = *(cmd->str);
// 	cmdwpath_len = ft_strlen(cmd_with_path);
// 	i = 0;
// 	cmd_len = 0;
// 	while (cmd_with_path[i])
// 	{
// 		cmd_len++;
// 		if (cmd_with_path[i] == '/')
// 			cmd_len = 0;
// 		i++;
// 	}
// 	cmd_wo_path = malloc((cmd_len + 1) * sizeof(char));
// 	if (!cmd_wo_path)
// 		return (-1);
// 	cmd_wo_path[cmd_len] = '\0';
// 	while (cmd_len--)
// 		*(cmd_wo_path + cmd_len) = *(cmd_with_path + --cmdwpath_len);
// 	ft_free_safe((void **)(&(cmd->str[0])));
// 	cmd->str[0] = cmd_wo_path;
// 	return (0);
// }

int	remove_path(t_str_list *cmd)
{
	char	*cmd_with_path;
	char	*cmd_wo_path;
	int		cmdlen[2];
	int		i;

	cmd_with_path = *(cmd->str);
	cmdlen[0] = ft_strlen(cmd_with_path);
	i = 0;
	cmdlen[1] = 0;
	while (cmd_with_path[i])
	{
		cmdlen[1]++;
		if (cmd_with_path[i] == '/')
			cmdlen[1] = 0;
		i++;
	}
	cmd_wo_path = malloc((cmdlen[1] + 1) * sizeof(char));
	if (!cmd_wo_path)
		return (-1);
	cmd_wo_path[cmdlen[1]] = '\0';
	while (cmdlen[1]--)
		*(cmd_wo_path + cmdlen[1]) = *(cmd_with_path + --cmdlen[0]);
	ft_free_safe((void **)(&(cmd->str[0])));
	return (cmd->str[0] = cmd_wo_path, 0);
}

// get_binary_path function that receives t_str_list pointer and returns int instead of char*
char	*get_binary_path(t_str_list *cmd, char **paths)
{
	char	*tmp[3];

	if (!(tmp[0] = ft_strdup(*(cmd->str))))
			return (perror("ft_strdup-malloc failed:"), NULL);
	if (access(tmp[0], F_OK) == 0)
		return (tmp[0]);
	while (*paths)
	{
		if (!(tmp[1] = ft_strjoin(*paths, "/")))
			return (free(tmp[0]), perror("tmp1-m failed:"), NULL);
		if (!(tmp[2] = ft_strjoin(tmp[1], *(cmd->str))))
			return (free(tmp[0]), free(tmp[1]), perror("tmp2-m failed:"), NULL);
		free(tmp[1]);
		if (access(tmp[2], F_OK) == 0)
			return (free(tmp[0]), tmp[2]);
		free(tmp[2]);
		paths++;
	}
	return (tmp[0]);
}

// // get_binary_path function that receives t_str_list pointer and returns int instead of char*
// char	*get_binary_path(t_str_list *cmd, char **paths)
// {
// 	char	*tmp[2];

// 	if (access(*(cmd->str), F_OK) == 0)
// 	{
// 		if (!(tmp[1] = ft_strdup(*(cmd->str))))
// 			return (perror("Couldn't malloc bin_path"), NULL);
// 		return (tmp[1]);
// 	}
// 	while (*paths)
// 	{
// 		if (!(tmp[0] = ft_strjoin(*paths, "/")))
// 			return (perror("Couldn't malloc tmp[0]"), NULL);
// 		if (!(tmp[1] = ft_strjoin(tmp[0], *(cmd->str))))
// 			return (free(tmp[0]), perror("Couldn't malloc tmp[1]"), NULL);
// 		free(tmp[0]);
// 		if (access(tmp[1], F_OK) == 0)
// 			return (tmp[1]);
// 		free(tmp[1]);
// 		paths++;
// 	}
// 	return (ft_fprintf(2, "pipex: %s: command not found\n", cmd->str[0]), NULL);
// }

// // get_binary_path function that receives t_str_list pointer and returns int instead of char*
// int	get_binary_path(t_str_list *cmd, char **paths, char **bin_path)
// {
// 	char	*tmp[2];

// 	if (access(*(cmd->str), F_OK) == 0)
// 	{
// 		if (!(*bin_path = ft_strdup(*(cmd->str))))
// 			return (perror("Couldn't malloc bin_path"), -2);
// 		return (0);
// 	}
// 	while (*paths)
// 	{
// 		if (!(tmp[0] = ft_strjoin(*paths, "/")))
// 			return (perror("Couldn't malloc tmp[0]"), -2);
// 		if (!(tmp[1] = ft_strjoin(tmp[0], *(cmd->str))))
// 			return (free(tmp[0]), perror("Couldn't malloc tmp[1]"), -2);
// 		free(tmp[0]);
// 		if (access(tmp[1], F_OK) == 0)
// 			return (*bin_path = tmp[1], 0);
// 		free(tmp[1]);
// 		paths++;
// 	}
// 	return (ft_fprintf(2, "pipex: %s: command not found\n", cmd->str[0]), 1);
// }


// // get_binary_path function that receives t_str_list pointer
// char	*get_binary_path(t_str_list *cmd, char **paths)
// {
// 	char	*tmp[2];

// 	if (access(*(cmd->str), F_OK) == 0)
// 	{
// 		tmp[1] = ft_strdup(*(cmd->str));
// 		if (!tmp[1])
// 			return (perror("Couldn't malloc tmp[1]"), NULL);
// 		return (tmp[1]);
// 	}
// 	while (*paths)
// 	{
// 		tmp[0] = ft_strjoin(*paths, "/");
// 		if (!tmp[0])
// 			return (NULL);
// 		tmp[1] = ft_strjoin(tmp[0], *(cmd->str));
// 		if (!tmp[1])
// 			return (free(tmp[0]), NULL);
// 		free(tmp[0]);
// 		if (access(tmp[1], F_OK) == 0)
// 			return (tmp[1]);
// 		free(tmp[1]);
// 		paths++;
// 	}
// 	return (NULL);
// }

// char	*get_binary_path(char *cmd, char **paths)
// {
// 	char	*tmp[2];

// 	if (access(cmd, F_OK) == 0)
// 	{
// 		tmp[1] = cmd;
// 		// if (remove_path(cmd) == -1)
// 		// 	return (perror("Remove_path-malloc failed"), NULL);
// 		return (tmp[1]);
// 	}
// 	while (*paths)
// 	{
// 		tmp[0] = ft_strjoin(*paths, "/");
// 		if (!tmp[0])
// 			return (NULL);
// 		tmp[1] = ft_strjoin(tmp[0], cmd);	// Fixed: Possible memory leaks here due to change of pointers from previous allocation
// 		if (!tmp[1])
// 			return (free(tmp[0]), NULL);
// 		free(tmp[0]);
// 		if (access(tmp[1], F_OK) == 0)
// 			return (tmp[1]);
// 		free(tmp[1]);
// 		paths++;
// 	}
// 	return (NULL);
// }
