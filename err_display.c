/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:11:20 by dakojic           #+#    #+#             */
/*   Updated: 2024/02/05 12:19:08 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	err_display(int flag, int err)
{
	if (flag == 0)
	{
		ft_putstr_fd("Required format: file1 cmd1 cmd2 file2\n", 1);
		exit(EXIT_FAILURE);
	}
	else if (flag == 1)
	{
		perror("Pipe failed.");
		exit(err);
	}
	else if (flag == 2)
	{
		perror("Forkfailed ");
		exit(err);
	}
	else if (flag == 3)
	{
		ft_putstr_fd("Command '' not found, but can be installed with:\n", 2);
		ft_putstr_fd("apt install mailutils-mh  # version 1:3.14-1, or\n", 2);
		ft_putstr_fd("apt install mmh           # version 0.4-4\n", 2);
		ft_putstr_fd("apt install nmh           # version 1.7.1-11\n", 2);
		ft_putstr_fd("apt install termtris      # version 1.3-1ubuntu1\n", 2);
		ft_putstr_fd("Ask your administrator to install one of them.\n", 2);
		exit(127);
	}
}
