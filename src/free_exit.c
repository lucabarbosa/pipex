/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:31:42 by lbento            #+#    #+#             */
/*   Updated: 2025/11/04 17:15:56 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_arguments(void);
void	free_cmd(char **array, char *argv);

void	error_arguments(void)
{
	ft_putstr_fd("Error: Invalid argument\n", 2);
	ft_putstr_fd("The arguments should be in this format:", 2);
	ft_putstr_fd("./pipex <file1> <cmd1> <cmd2> <file2>\n", 2);
	exit (1);
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
		exit (1);
	}
}