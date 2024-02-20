/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:10:38 by dakojic           #+#    #+#             */
/*   Updated: 2024/02/20 15:41:14 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/* || (ft_strcmp(path, arguments[0])
			&& path_check(arguments[0]) == 0))*/
static void	launcher(char *av, char **env)
{
	char	*path;
	char	**arguments;

	if (av[0] == '\0')
		err_display(3, 0);
	arguments = ft_split(av, ' ');
	if (!arguments)
		exit(1);
	path = get_path(arguments[0], env);
	if (!path)
	{
		free_array(arguments);
		exit(1);
	}
	execve(path, arguments, env);
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putstr_fd(arguments[0], 2);
	ft_putstr_fd("\n", 2);
	if (arguments)
		free_array(arguments);
	if (!env[0])
		exit(1);
	exit(127);
}

static int	open_fd(char *av, int check)
{
	int	fd;

	fd = 0;
	if (check == 0)
	{
		if (access(av, F_OK))
		{
			perror(av);
			exit(1);
		}
		fd = open(av, O_RDONLY);
	}
	else if (check == 1)
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(av);
		exit(1);
	}
	return (fd);
}

static void	child_worker(char **av, int *end, char **env)
{
	int	fd;

	fd = open_fd(av[1], 0);
	if (dup2(fd, 0) == -1 || dup2(end[1], 1) == -1)
	{
		perror("dup failed");
		exit(1);
	}
	close(end[0]);
	close(end[1]);
	close(fd);
	launcher(av[2], env);
	return ;
}

static void	parent_worker(char **av, int *end, char **env)
{
	int	fd;

	fd = open_fd(av[4], 1);
	if (dup2(end[0], 0) == -1 || dup2(fd, 1) == -1)
	{
		perror("dup failed");
		exit(1);
	}
	close(end[1]);
	close(end[0]);
	close(fd);
	launcher(av[3], env);
	return ;
}

// int	main(int ac, char **av, char **env)
// {
// 	int		status;
// 	int		end[2];
// 	pid_t	parent;

// 	if (ac != 5)
// 		err_display(0, 0);
// 	if (pipe(end) == -1)
// 		err_display(1, errno);
// 	parent = fork();
// 	if (parent == -1)
// 		err_display(2, errno);
// 	if (!parent)
// 		child_worker(av, end, env);
// 	else
// 	{

// 	}

// 	exit(EXIT_SUCCESS);
// }

int	main(int ac, char **av, char **env)
{
	int		status;
	int		end[2];
	pid_t	first;
	pid_t	second;
	if (ac != 5)
		err_display(0, 0);
	if (pipe(end) == -1)
		err_display(1, errno);
	first = fork();
	if (first == -1)
		err_display(2, errno);
	if (!first)
	{
		child_worker(av, end, env);

	}
	else
	{
		second = fork();
		if(second == -1)
			err_display(2, errno);
		if(!second)
		{
			parent_worker(av, end, env);
		}
		else
		{
			close(end[0]);
			close(end[1]);
			waitpid(first, NULL, 0);
			wait(&status);
			if(status != 0)
				exit(1);
		}
	}	
	exit(EXIT_SUCCESS);
}
