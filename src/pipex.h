/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:27:23 by lbento            #+#    #+#             */
/*   Updated: 2025/11/05 16:34:06 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	int		pipe_rw[2];
	char	*infile;
	char	*outfile;
	char	**cmd_1;
	char	**cmd_2;
}	t_pipex;

int		is_space(char *str);
void	empty_command(void);
void	error_arguments(void);
void	get_path(char **cmd, char **envp);
void	free_cmd(char **array, char *argv);
pid_t	cmd_pipe_exec(t_pipex *infos, char **env);
void	free_and_exit(char **cmd_1, char **cmd_2, int exit_status);

#endif