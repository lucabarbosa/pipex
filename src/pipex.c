/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:26:57 by lbento            #+#    #+#             */
/*   Updated: 2025/11/05 11:22:41 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	infos;
	pid_t		pid;
	int		status;

	if (argc == 5)
	{
		infos.infile = argv[1];
		infos.outfile = argv[4];
		infos.cmd_1 = ft_split(argv[2], ' ');
		if (!infos.cmd_1 || !infos.cmd_1[0])
			free_cmd(infos.cmd_1, argv[2]);
		infos.cmd_2 = ft_split(argv[3], ' ');
		if (!infos.cmd_2 || !infos.cmd_2[0])
		{
			free_cmd(infos.cmd_1, NULL);
			free_cmd(infos.cmd_2, argv[3]);
		}
		get_path(infos.cmd_1, envp);
		get_path(infos.cmd_2, envp);
		pid = cmd_pipe_exec(&infos, envp);
			waitpid(pid, &status, 0);
		free_and_exit(infos.cmd_1, infos.cmd_2, WEXITSTATUS(status));
	}
	else
		error_arguments();
}
