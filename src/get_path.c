/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:50:03 by lbento            #+#    #+#             */
/*   Updated: 2025/11/04 19:36:54 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_path(char **cmd, char **envp);
static char	**get_envp_path(char **envp);
static char	**getting_part_path (char **envp);
static int	join_path_and_cmd(char **cmd, char **paths);

void	get_path(char **cmd, char **envp)
{
	char	**cmd_paths;

	cmd_paths = get_envp_path(envp);
	if (!cmd_paths)
	{
		free_cmd(cmd, NULL);
		exit(1);
	}
	if (access(cmd[0], X_OK) != 0)
	{
		if (join_path_and_cmd(&cmd[0], cmd_paths) == -1)
		{
			free_cmd(cmd, NULL);
			free_cmd(cmd_paths, NULL);
			exit (1);
		}
	}
	free_cmd(cmd_paths, NULL);
}

static char	**get_envp_path(char **envp)
{
	char	**parted_path;
	char	*temp;
	int	i;
	
	parted_path = getting_part_path(envp);
	if (!parted_path)
		return (NULL);
	i = 0;
	while (parted_path[i])
	{
		temp = ft_strjoin(parted_path[i], "/");
		if (!temp)
		{
			free_cmd(parted_path, NULL);
			return (NULL);
		}
		free(parted_path[i]);
		parted_path[i] = temp;
		i++;
	}
	return (parted_path);
}

static char	**getting_part_path (char **envp)
{
	int	i;
	char **parting_path;
	
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
			break ;
		i++;
	}
	if (!envp || !envp[i])
	{
		ft_putstr_fd("ERROR: PATH not found\n", 2);
		return (NULL);
	}
	parting_path = ft_split(envp[i] + 5, ':');
	if (!parting_path)
		return (NULL);
	return (parting_path);
}

static int	join_path_and_cmd(char **cmd, char **paths)
{
	char	*temp;
	size_t	i;
	
	i = 0;
	while (paths && paths[i])
	{
		temp = ft_strjoin(paths[i], *cmd);
		if (!temp)
		{
			perror("ERROR: failed to create full command path\n");
			return (-1);
		}
		if (access(temp, X_OK) == 0)
		{
			free(*cmd);
			*cmd = temp;
			return (0);
		}
		free(temp);
		i++;
	}
	return (0);
}
