/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:07:34 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/10 00:02:11 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int		get_binaries(t_input *ag, t_pipex *data);
char	**get_paths(char **envp);
void	get_commands(t_input *ag, t_pipex *data);
char	*get_binary_path(t_str_list *cmd, char **paths);
int		remove_path(t_str_list *cmd);

int	get_binaries(t_input *ag, t_pipex *data)
{
	data->paths = get_paths(ag->env_vars);
	if (!(data->paths))
	{
		perror("Couldn't get paths");
		free_exit(data, EXIT_FAILURE);
	}
	get_commands(ag, data);
	data->bin_path1 = get_binary_path(&(data->cmd1), data->paths);
	if (!(data->bin_path1))
		return (free_fields(data), 127);
	data->bin_path2 = get_binary_path(&(data->cmd2), data->paths);
	if (!(data->bin_path2))
		return (free_fields(data), 127);
	if (remove_path(&(data->cmd1)) == -1)
		return (perror("Remove_path-malloc failed"), -1);
	if (remove_path(&(data->cmd2)) == -1)
		return (perror("Remove_path-malloc failed"), -1);
	return (0);
}

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

void	get_commands(t_input *ag, t_pipex *data)
{
	data->cmd1.str = ft_parse(ag->agv[2]);
	if (!(data->cmd1.str))
	{
		perror("Parse error cmd1");
		free_exit(data, EXIT_FAILURE);
	}
	data->cmd2.str = ft_parse(ag->agv[3]);
	if (!(data->cmd2.str))
	{
		perror("Parse error cmd2");
		free_exit(data, EXIT_FAILURE);
	}
}

char	*get_binary_path(t_str_list *cmd, char **paths)
{
	char	*tmp[3];

	tmp[0] = ft_strdup(*(cmd->str));
	if (!(tmp[0]))
		return (perror("ft_strdup-malloc failed:"), NULL);
	if (access(tmp[0], F_OK) == 0)
		return (tmp[0]);
	while (*paths)
	{
		tmp[1] = ft_strjoin(*paths, "/");
		if (!(tmp[1]))
			return (free(tmp[0]), perror("tmp1-m failed:"), NULL);
		tmp[2] = ft_strjoin(tmp[1], *(cmd->str));
		if (!(tmp[2]))
			return (free(tmp[0]), free(tmp[1]), perror("tmp2-m failed:"), NULL);
		free(tmp[1]);
		if (access(tmp[2], F_OK) == 0)
			return (free(tmp[0]), tmp[2]);
		free(tmp[2]);
		paths++;
	}
	return (tmp[0]);
}

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
	cmd->str[0] = cmd_wo_path;
	return (0);
}
