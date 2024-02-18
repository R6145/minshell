/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excuationiii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:24:04 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/02/18 19:38:24 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(char **argv, char **envp, int **pipe_fd, t_minishell *mini)
{
	int	fd;

	fd = open(argv[mini->temp[0] - 2], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		return (close_pipe(pipe_fd, mini->temp[1]), free_pipe(pipe_fd),
			exit(3));
	}
	if (dup2(fd, STDIN_FILENO) == -1 || dup2(pipe_fd[mini->temp[0] - 3][1],
		STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Dup Error\n", 2);
		close(fd);
		return (close_pipe(pipe_fd, mini->temp[1]), free_pipe(pipe_fd),
			exit(4));
	}
	close_pipe(pipe_fd, mini->temp[1]);
	close(fd);
	if (excute_command(argv, envp, mini->temp[0] - 1) == -1)
		return (free_pipe(pipe_fd), exit(127));
}

void	middle_child(char **argv, char **envp, int **pipe_fd, int i[2])
{
	if (dup2(pipe_fd[i[0] - 3][0], STDIN_FILENO) == -1 || dup2(pipe_fd[i[0]
			- 2][1], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Dup Error\n", 2);
		return (close_pipe(pipe_fd, i[1]), free_pipe(pipe_fd), exit(4));
	}
	close_pipe(pipe_fd, i[1]);
	if (excute_command(argv, envp, i[0]) == -1)
		return (free_pipe(pipe_fd), exit(127));
}

void	middle(char **argv, char **envp, int **pipe_fd, int i[2])
{
	pid_t	pid;

	pid = forking(pipe_fd, i[1]);
	if (pid == 0)
	{
		wait(NULL);
		middle_child(argv, envp, pipe_fd, i);
	}
}

void	parent(char **argv, char **envp, int **pipe_fd, int i)
{
	int	fd;

	fd = open(argv[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		return (close_pipe(pipe_fd, i + 2), free_pipe(pipe_fd), exit(1));
	}
	if (dup2(fd, STDOUT_FILENO) == -1 || dup2(pipe_fd[i - 3][0],
		STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Dup Error\n", 2);
		close(fd);
		return (close_pipe(pipe_fd, i + 2), free_pipe(pipe_fd), exit(4));
	}
	close_pipe(pipe_fd, i + 2);
	close(fd);
	if (excute_command(argv, envp, i) == -1)
		return (free_pipe(pipe_fd), exit(127));
}

int	pipex(int argc, char **argv, char **envp, t_minishell *mini)
{
	pid_t	pid;
	int		**fd;

	mini->temp[0] = 3;
	mini->temp[1] = argc;
	fd = fd_create(argc);
	pid = forking(fd, argc);
	if (pid == 0)
		child(argv, envp, fd, mini);
	while (mini->temp[0] < argc - 2)
	{
		middle(argv, envp, fd, mini->temp);
		mini->temp[0]++;
	}
	parent(argv, envp, fd, argc - 2);
	return (0);
}
