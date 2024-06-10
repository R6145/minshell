/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excuationv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:24:04 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/06/10 19:10:33 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_dumbf_in(int i, char **argv, int **pipe_fd, t_minishell *mini)
{
	int		fd2;
	char	*file;
	char	*temp;

	file = get_filename_out(argv[mini->temp[0] + i]);
	if (file != NULL)
	{
		create_dumby_files(argv[mini->temp[0] + i], pipe_fd, mini);
		if (check_out_type(argv[mini->temp[0] + i]) == 2)
			fd2 = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd2 = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		temp = argv[mini->temp[0] + i];
		argv[mini->temp[0] + i] = cleanup_output(argv[mini->temp[0] + i]);
		free(temp);
		if (fd2 == -1)
			return (free(file), free_error_fd(pipe_fd, mini));
		mini->temp[2] = dup2(fd2, STDOUT_FILENO);
		close(fd2);
		free(file);
	}
	else
		mini->temp[2] = dup2(pipe_fd[mini->temp[0] - 2 + i][1], STDOUT_FILENO);
	if (mini->temp[2] == -1)
		free_error_dup(pipe_fd, mini, fd2);
}

void	create_dumbf_out(char **argv, int **pipe_fd, t_minishell *mini)
{
	char	*file;
	char	*temp;
	int		fd;

	file = get_filename_out(argv[mini->temp[0]]);
	if (file != NULL)
	{
		create_dumby_files(argv[mini->temp[0]], pipe_fd, mini);
		if (check_out_type(argv[mini->temp[0]]) == 2)
			fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		temp = argv[mini->temp[0]];
		argv[mini->temp[0]] = cleanup_output(argv[mini->temp[0]]);
		free(temp);
		free(file);
	}
	else
		fd = open(argv[mini->temp[1] - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		free_error_fd(pipe_fd, mini);
	dup2(fd, STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
		free_error_dup(pipe_fd, mini, fd);
	close(fd);
}

char	*input_code(char *file, char *argv, int **pipe_fd, t_minishell *mini)
{
	int		fd;
	char	*temp;

	fd = 0;
	if (check_in_type(argv) == 1)
	{
		fd = open(file, O_RDONLY);
		temp = argv;
		argv = cleanup_input(argv);
		free(temp);
	}
	else
	{
		fd = here_doc(argv, mini, pipe_fd);
		temp = argv;
		argv = cleanup_input(argv);
		free(temp);
	}
	mini->temp[2] = fd;
	return (argv);
}

char	*input_code_s(char *file, char *argv, int **pipe_fd, t_minishell *mini)
{
	int		fd;
	char	*temp;

	fd = 0;
	if (check_in_type(argv) == 1)
	{
		fd = open(file, O_RDONLY);
		temp = argv;
		argv = cleanup_input(argv);
		free(temp);
	}
	else
	{
		fd = here_doc(argv, mini, pipe_fd);
		temp = argv;
		argv = cleanup_input(argv);
		free(temp);
	}
	mini->temp[0] = fd;
	return (argv);
}

char	*create_dumbf_outs(char *argv, t_minishell *mini)
{
	char	*file;
	char	*temp;
	int		fd;

	file = get_filename_out(argv);
	if (file != NULL)
	{
		create_dumby_files(argv, NULL, mini);
		if (check_out_type(argv) == 2)
			fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		temp = argv;
		argv = cleanup_output(argv);
		free(temp);
		free(file);
	}
	else
		fd = open("/dev/tty", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		free_error_fd(NULL, mini);
	if (dup2(fd, STDOUT_FILENO) == -1)
		free_error_dup(NULL, mini, fd);
	close(fd);
	return (argv);
}
