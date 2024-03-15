/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excuationii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:16:44 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/03/15 18:26:01 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	forking(int **fd, int argc)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Fork failed\n", 2);
		return (close_pipe(fd, argc), free_pipe(fd), exit(5), 0);
	}
	return (pid);
}

int	**fd_create(int argc)
{
	int	**x;
	int	i;

	i = 0;
	x = malloc(sizeof(int *) * (argc - 3));
	if (!x)
		return (ft_putstr_fd("insuffiecnt memory", 2), exit(22), NULL);
	while (i < argc - 4)
	{
		x[i] = malloc(sizeof(int) * (2));
		if (!x[i])
		{
			free_pipe(x);
			return (ft_putstr_fd("insuffiecnt memory", 2), exit(22), NULL);
		}
		i++;
	}
	x[i] = NULL;
	piping(x, argc);
	return (x);
}

void	piping(int **x, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 4)
	{
		if (pipe(x[i]) == -1)
		{
			ft_putstr_fd("Pipe failed\n", 2);
			free_pipe(x);
			exit(5);
		}
		i++;
	}
}

void	close_pipe(int **fd, int argc)
{
	int	i;

	i = 0;
	if (fd == NULL)
		return ;
	while (i < argc - 4)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	free_pipe(int **fd)
{
	int	i;

	i = 0;
	if (fd == NULL)
		return ;
	while (fd[i] != NULL)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
