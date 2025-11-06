/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:10:50 by lbento            #+#    #+#             */
/*   Updated: 2025/11/05 17:56:17 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_in_out(int child_i, t_pipex *infos, int last_read_end);
static int	in_out_direction(int input_fd, int output_fd);
static void	exec_cmd(int child_i, t_pipex *infos, char **env);
static void	close_unused(int child_i, t_pipex *infos, int read_end);

pid_t	cmd_pipe_exec(t_pipex *infos, char **env)
{
	pid_t	pid;
	int		read_end;
	int		i;

	i = 0;
	read_end = -1;
	while (i < 2)
	{
		if (i == 0 && pipe(infos->pipe_rw) == -1)
			free_and_exit(infos->cmd_1, infos->cmd_2, 1);
		pid = fork();
		if (pid == -1)
			free_and_exit(infos->cmd_1, infos->cmd_2, 1);
		else if (pid == 0)
		{
			set_in_out(i, infos, read_end);
			exec_cmd(i, infos, env);
		}
		close_unused(i, infos, read_end);
		read_end = infos->pipe_rw[0];
		i++;
	}
	return (pid);
}

static void	set_in_out(int child_i, t_pipex *infos, int last_read_end)
{
	int	fds[2];

	if (child_i == 0)
		fds[0] = open(infos->infile, O_RDONLY);
	else
		fds[0] = last_read_end;
	if (child_i == 1)
		fds[1] = open(infos->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
	{
		if (close(infos->pipe_rw[0]) == -1)
			free_and_exit(infos->cmd_1, infos->cmd_2, 1);
		fds[1] = infos->pipe_rw[1];
	}
	if (fds[0] == -1 || fds[1] == -1)
		free_and_exit(infos->cmd_1, infos->cmd_2, 1);
	if (in_out_direction(fds[0], fds[1]) == -1)
		free_and_exit(infos->cmd_1, infos->cmd_2, 1);
}

static int	in_out_direction(int input_fd, int output_fd)
{
	if (dup2(input_fd, 0) == -1)
		return (-1);
	if (input_fd != 0)
	{
		if (close(input_fd) == -1)
			return (-1);
	}
	if (dup2(output_fd, 1) == -1)
		return (-1);
	if (output_fd != 1)
	{
		if (close(output_fd) == -1)
			return (-1);
	}
	return (0);
}

static void	exec_cmd(int child_i, t_pipex *infos, char **env)
{
	if (child_i == 0)
	{
		if (execve(infos->cmd_1[0], infos->cmd_1, env) == -1)
			free_and_exit(infos->cmd_1, infos->cmd_2, 127);
	}
	else
	{
		if (execve(infos->cmd_2[0], infos->cmd_2, env) == -1)
			free_and_exit(infos->cmd_1, infos->cmd_2, 127);
	}
}

static void	close_unused(int child_i, t_pipex *infos, int read_end)
{
	if (child_i != 1)
	{
		if (close(infos->pipe_rw[1]) == -1)
			free_and_exit(infos->cmd_1, infos->cmd_2, 1);
	}
	if (child_i != 0)
	{
		if (close(read_end) == -1)
			free_and_exit(infos->cmd_1, infos->cmd_2, 1);
	}
}
