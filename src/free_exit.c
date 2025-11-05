/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:31:42 by lbento            #+#    #+#             */
/*   Updated: 2025/11/05 15:33:52 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		is_space(char *str);
void	error_arguments(void);
void	free_cmd(char **array, char *argv);
void	empty_command(void);
void	free_and_exit(char **cmd_1, char **cmd_2, int exit_status);

void	error_arguments(void)
{
	ft_putstr_fd("Error: Invalid argument\n", 2);
	ft_putstr_fd("The arguments should be in this format:", 2);
	ft_putstr_fd("./pipex <file1> <cmd1> <cmd2> <file2>\n", 2);
	exit (1);
}

void	empty_command(void)
{
	ft_putstr_fd(" : command not found\n", 2);
	exit (127);
}

void	free_cmd(char **array, char *msg)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	if (msg)
	{
		perror(msg);
		exit (127);
	}
}

void	free_and_exit(char **cmd_1, char **cmd_2, int exit_status)
{
	while (wait(NULL) != -1)
		continue ;
	free_cmd(cmd_1, NULL);
	free_cmd(cmd_2, NULL);
	exit(exit_status);
}

int	is_space(char *str)
{
	int	i;

	if (!str || !str[0])
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
