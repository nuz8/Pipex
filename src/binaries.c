/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:07:34 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/04 03:02:11 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int		get_binaries(t_pipex *data);
char	**get_paths(char **envp);

// int		get_cmdlen(char *cmd_with_path);
// char	*remove_path(char *cmd_with_path);
// int		remove_path(t_str_list *cmd);

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
		free_fields(data);
		perror("Parse error cmd1");
		exit(127);
	}
		// return (free_fields(data), perror("Parse error cmd1"), 2);

	data->cmd2.str = ft_parse(data->argV[3]);
	if (!data->cmd2.str)
	{
		free_fields(data);
		perror("Parse error cmd2");
		exit (127);
	}
		// return (free_fields(data), perror("Parse error cmd1"), 2);

	// data->bin_path1 = get_binary_path((data->cmd1.str[0]), data->paths);
	data->bin_path1 = get_binary_path(&(data->cmd1), data->paths);
	if (!data->bin_path1)
	{
		// free_fields(data);
		perror("command not found (bp1) lalalalallaalllalal");
		// write(2, "command not found (bp1) lalalalallaalllalal\n", 44);
		// ft_printf("pipex: %s: command not found", data->cmd1.str[0]);
		// return(127);
	}
		// return (free_fields(data), perror("Couldn't get path1"), 2);
	
	// data->bin_path2 = get_binary_path((data->cmd2.str[0]), data->paths);
	data->bin_path2 = get_binary_path(&(data->cmd2), data->paths);
	if (!data->bin_path2)
	{
		free_fields(data);
		perror("command not found (bp2) lalalalala");
		// write(2, "command not found (bp1) lalalalalla\n", 36);
		// ft_printf("pipex: %s: command not found", data->cmd2.str[0]);
		// exit(127);
	}
		// return (free_fields(data), perror("Couldn't get path2"), 2);
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

// int	get_cmdlen(char *cmd_with_path)
// {
// 	int	cmdlen;

// 	cmdlen = 0;
// 	while (*cmd_with_path)
// 	{
// 		cmdlen++;
// 		if (*cmd_with_path == '/')
// 			cmdlen = 0;
// 		cmd_with_path++;
// 	}
// }

// char	*remove_path(char *cmd_with_path)
// {
// 	char	*cmd_wo_path;
// 	int		cmd_len;
// 	int		cmdwpath_len;

// 	cmd_len = get_cmdlen(cmd_with_path);
// 	cmdwpath_len = ft_strlen(cmd_with_path);
// 	cmd_wo_path = malloc((cmd_len + 1) * sizeof(char));
// 	if (!cmd_wo_path)
// 		return (NULL);
// 	cmd_wo_path[cmd_len] = '\0';
// 	while (cmd_len--)
// 		*(cmd_wo_path + cmd_len) = *(cmd_with_path + --cmdwpath_len);
// 	free(cmd_with_path);
// 	return (cmd_wo_path);
// }

// This function integrates the above two funcitons: remove_path and get_cmdlen
// into a single function
int	remove_path(t_str_list *cmd)
{
	char	*cmd_with_path;
	char	*cmd_wo_path;
	int		cmd_len;
	int		cmdwpath_len;
	int		i;

	cmd_with_path = *(cmd->str);
	cmdwpath_len = ft_strlen(cmd_with_path);
	i = 0;
	cmd_len = 0;
	while (cmd_with_path[i])
	{
		cmd_len++;
		if (cmd_with_path[i] == '/')
			cmd_len = 0;
		i++;
	}
	cmd_wo_path = malloc((cmd_len + 1) * sizeof(char));
	if (!cmd_wo_path)
		return (-1);
	cmd_wo_path[cmd_len] = '\0';
	while (cmd_len--)
		*(cmd_wo_path + cmd_len) = *(cmd_with_path + --cmdwpath_len);
	// free(cmd->str[0]);
	ft_free_safe(&(cmd->str[0]));
	cmd->str[0] = cmd_wo_path;
	return (0);
}

// get_binary_path function that receives t_str_list pointer
char	*get_binary_path(t_str_list *cmd, char **paths)
{
	char	*bin;
	char	*tmp;

	if (access(*(cmd->str), F_OK) == 0)
	{
		bin = ft_strdup(*(cmd->str));
		if (!bin)
			return (perror("Couldn't malloc bin"), NULL);
		if (remove_path(cmd) == -1)
			return (perror("Remove_path-malloc failed"), NULL);
		return (bin);
	}
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (NULL);
		bin = ft_strjoin(tmp, *(cmd->str));	// Fixed: Possible memory leaks here due to change of pointers from previous allocation
		if (!bin)
			return (free(tmp), NULL);
		free(tmp);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		paths++;
	}
	return (NULL);
}

// char	*get_binary_path(char *cmd, char **paths)
// {
// 	char	*bin;
// 	char	*tmp;

// 	if (access(cmd, F_OK) == 0)
// 	{
// 		bin = cmd;
// 		// if (remove_path(cmd) == -1)
// 		// 	return (perror("Remove_path-malloc failed"), NULL);
// 		return (bin);
// 	}
// 	while (*paths)
// 	{
// 		tmp = ft_strjoin(*paths, "/");
// 		if (!tmp)
// 			return (NULL);
// 		bin = ft_strjoin(tmp, cmd);	// Fixed: Possible memory leaks here due to change of pointers from previous allocation
// 		if (!bin)
// 			return (free(tmp), NULL);
// 		free(tmp);
// 		if (access(bin, F_OK) == 0)
// 			return (bin);
// 		free(bin);
// 		paths++;
// 	}
// 	return (NULL);
// }
