/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excuationiii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:24:04 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/02/23 15:09:27 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(char **argv, char **envp, int **pipe_fd, t_minishell *mini)
{
	int		fd;
	int		fd2;
	char	*file;
	char	*temp;

	fd = open_file(mini, argv, pipe_fd);
	file = get_filename_out(argv[mini->temp[0] - 1]);
	if (file != NULL)
	{
		create_dumby_files(argv[mini->temp[0] - 1]);
		if (check_out_type(argv[mini->temp[0] - 1]) == 2)
			fd2 = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd2 = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		temp = argv[mini->temp[0] - 1];
		argv[mini->temp[0] - 1] = cleanup_output(argv[mini->temp[0] - 1]);
		free(temp);
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
		free(file);
	}
	else
		dup2(pipe_fd[mini->temp[0] - 3][1], STDOUT_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Dup Error\n", 2);
		close(fd);
		return (close_pipe(pipe_fd, mini->temp[1]), free_pipe(pipe_fd),
			exit(4));
	}
	close_pipe(pipe_fd, mini->temp[1]);
	close(fd);
	// if (file != NULL)
	// 	close(fd2);
	if (excute_command(argv, envp, mini->temp[0] - 1) == -1)
		return (free_pipe(pipe_fd), exit(127));
}

void	middle_child(char **argv, char **envp, int **pipe_fd, t_minishell *mini)
{
	char	*file;
	char	*temp;
	int		fd;
	int		fd2;

	file = get_filename(argv[mini->temp[0]]);
	if (file != NULL)
	{
		fd = open(file, O_RDONLY);
		temp = argv[mini->temp[0]];
		argv[mini->temp[0]] = cleanup_input(argv[mini->temp[0]]);
		free(temp);
		dup2(fd, STDIN_FILENO);
		close(fd);
		free(file);
	}
	else
		dup2(pipe_fd[mini->temp[0] - 3][0], STDIN_FILENO);
	file = get_filename_out(argv[mini->temp[0]]);
	if (file != NULL)
	{
		create_dumby_files(argv[mini->temp[0]]);
		if (check_out_type(argv[mini->temp[0]]) == 2)
			fd2 = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd2 = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		temp = argv[mini->temp[0]];
		argv[mini->temp[0]] = cleanup_output(argv[mini->temp[0]]);
		free(temp);
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
	}
	else
		dup2(pipe_fd[mini->temp[0] - 2][1], STDOUT_FILENO);
	// if (dup2(pipe_fd[mini->temp[0] - 2][1], STDOUT_FILENO) == -1)
	// {
	// ft_putstr_fd("Dup Error\n", 2);
	// return (close_pipe(pipe_fd, mini->temp[1]), free_pipe(pipe_fd),
	// 	exit(4));
	// }
	close_pipe(pipe_fd, mini->temp[1]);
	// if (file != NULL)
	// 	close(fd);
	if (excute_command(argv, envp, mini->temp[0]) == -1)
		return (free_pipe(pipe_fd), exit(127));
}

void	middle(char **argv, char **envp, int **pipe_fd, t_minishell *mini)
{
	pid_t	pid;

	pid = forking(pipe_fd, mini->temp[1]);
	if (pid == 0)
	{
		wait(NULL);
		middle_child(argv, envp, pipe_fd, mini);
	}
}

void	parent(char **argv, char **envp, int **pipe_fd, t_minishell *mini)
{
	int		fd;
	char	*file;
	char	*temp;
	int		fd2;

	file = get_filename(argv[mini->temp[0]]);
	if (file != NULL)
	{
		fd2 = open(file, O_RDONLY);
		temp = argv[mini->temp[0]];
		argv[mini->temp[0]] = cleanup_input(argv[mini->temp[0]]);
		free(temp);
		dup2(fd2, STDIN_FILENO);
		close(fd2);
		free(file);
	}
	else
		dup2(pipe_fd[mini->temp[1] - 5][0], STDIN_FILENO);
	file = get_filename_out(argv[mini->temp[0]]);
	if (file != NULL)
	{
		create_dumby_files(argv[mini->temp[0]]);
		if (check_out_type(argv[mini->temp[0]]) == 2)
			fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		temp = argv[mini->temp[0]];
		argv[mini->temp[0]] = cleanup_output(argv[mini->temp[0]]);
		free(temp);
		dup2(fd, STDOUT_FILENO);
		free(file);
	}
	else
	{
		fd = open(argv[mini->temp[1] - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
			return (close_pipe(pipe_fd, mini->temp[1]), free_pipe(pipe_fd),
				exit(1));
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("Dup Error\n", 2);
			close(fd);
			return (close_pipe(pipe_fd, mini->temp[1]), free_pipe(pipe_fd),
				exit(4));
		}
	}
	close_pipe(pipe_fd, mini->temp[1]);
	close(fd);
	// if (file != NULL)
	// 	close(fd2);
	if (excute_command(argv, envp, mini->temp[1] - 2) == -1)
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
		middle(argv, envp, fd, mini);
		mini->temp[0]++;
	}
	parent(argv, envp, fd, mini);
	return (0);
}
