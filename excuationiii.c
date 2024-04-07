/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excuationiii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:24:04 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/04/07 19:58:38 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(char **argv, int **pipe_fd, t_minishell *mini)
{
	int	fd;

	fd = open_file(mini, argv, pipe_fd);
	create_dumbf_in(-1, argv, pipe_fd, mini);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Dup Error\n", 2);
		close(fd);
		free_mini(mini);
		return (close_pipe(pipe_fd, mini->temp[1]), free_pipe(pipe_fd),
			exit(4));
	}
	close_pipe(pipe_fd, mini->temp[1]);
	close(fd);
	excute_code(argv, pipe_fd, mini, mini->temp[0] - 1);
}

void	middle_child(char **argv, int **pipe_fd, t_minishell *mini)
{
	char	*file;
	int		temp;

	file = get_filename(argv[mini->temp[0]]);
	if (file != NULL)
	{
		argv[mini->temp[0]] = input_code(file, argv[mini->temp[0]], pipe_fd,
				mini);
		if (mini->temp[2] == -1)
			return (free(file), free_error_fd(pipe_fd, mini));
		temp = mini->temp[2];
		mini->temp[2] = dup2(mini->temp[2], STDIN_FILENO);
		close(temp);
		free(file);
	}
	else
		mini->temp[2] = dup2(pipe_fd[mini->temp[0] - 3][0], STDIN_FILENO);
	if (mini->temp[2] == -1)
		free_error_dup(pipe_fd, mini, mini->temp[2]);
	create_dumbf_in(0, argv, pipe_fd, mini);
	close_pipe(pipe_fd, mini->temp[1]);
	excute_code(argv, pipe_fd, mini, mini->temp[0]);
}

void	middle(char **argv, int **pipe_fd, t_minishell *mini)
{
	pid_t	pid;

	if (check_here_doc(argv, mini->temp[0] - 1) == 1)
		wait(NULL);
	pid = forking(pipe_fd, mini->temp[1]);
	if (pid == 0)
	{
		wait(NULL);
		middle_child(argv, pipe_fd, mini);
	}
}

void	parent(char **argv, int **pipe_fd, t_minishell *mini)
{
	char	*file;
	int		temp;

	file = get_filename(argv[mini->temp[0]]);
	if (file != NULL)
	{
		argv[mini->temp[0]] = input_code(file, argv[mini->temp[0]], pipe_fd,
				mini);
		if (mini->temp[2] == -1)
			return (free(file), free_error_fd(pipe_fd, mini));
		temp = mini->temp[2];
		mini->temp[2] = dup2(mini->temp[2], STDIN_FILENO);
		close(temp);
		free(file);
	}
	else
		mini->temp[2] = dup2(pipe_fd[mini->temp[1] - 5][0], STDIN_FILENO);
	if (mini->temp[2] == -1)
		free_error_dup(pipe_fd, mini, mini->temp[2]);
	create_dumbf_out(argv, pipe_fd, mini);
	close_pipe(pipe_fd, mini->temp[1]);
	excute_code(argv, pipe_fd, mini, mini->temp[1] - 2);
}

int	pipex(int argc, char **argv, t_minishell *mini)
{
	pid_t	pid;
	int		**fd;

	mini->temp[0] = 3;
	mini->temp[1] = argc;
	fd = fd_create(argc);
	pid = forking(fd, argc);
	if (pid == 0)
		child(argv, fd, mini);
	while (mini->temp[0] < argc - 2)
	{
		middle(argv, fd, mini);
		mini->temp[0]++;
	}
	if (check_here_doc(argv, mini->temp[1] - 3) == 1)
		wait(NULL);
	parent(argv, fd, mini);
	return (0);
}
