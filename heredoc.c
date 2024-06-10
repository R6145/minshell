/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:36:43 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/06/10 18:16:20 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**here_maker(char *cmd)
{
	int		i;
	int		j;
	char	**names;

	i = 0;
	j = ft_strlen(cmd) - 1;
	names = malloc(sizeof(char *) * (j + 2));
	while (j >= 0)
	{
		if (cmd[j] == '<' && between_quo(cmd, j) == 0)
		{
			j--;
			if (cmd[j] == '<')
				names[i++] = get_filename_pos(cmd, j + 1);
		}
		j--;
	}
	names[i] = NULL;
	return (names);
}

int	here_doc_extra(char *cmd, int fd[2], t_minishell *mini, int **pipe_fd)
{
	int		i;
	char	**names;

	i = 0;
	names = here_maker(cmd);
	i = amount_of_arg(names) - 1;
	g_signal_var = fd[1];
	while (i >= 0)
	{
		cmd = readline(">");
		if (cmd == NULL || g_signal_var == -3)
			break ;
		if (ft_strncmp(cmd, names[i], ft_strlen(names[i]) + 2) == 0)
		{
			if (i == 0)
				break ;
			i--;
		}
		write(fd[1], cmd, ft_strlen(cmd));
		write(fd[1], "\n", 1);
		free(cmd);
	}
	return ((free(cmd), close(fd[1]), close(fd[0]), free_split(names),
			free_mini(mini), close_pipe(pipe_fd, mini->temp[1])),
		free_pipe(pipe_fd), exit(0), 0);
}

pid_t	here_doc_f(int fd[2], t_minishell *mini, int **pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Fork failed\n", 2);
		close(fd[1]);
		close(fd[0]);
		free_mini(mini);
		return (close_pipe(pipe_fd, mini->temp[1]), free_pipe(pipe_fd), exit(5),
			0);
	}
	return (pid);
}

int	here_doc(char *cmd, t_minishell *mini, int **pipe_fd)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Pipe failed\n", 2);
		free_mini(mini);
		return (close_pipe(pipe_fd, mini->temp[1]), free_pipe(pipe_fd), exit(5),
			0);
	}
	wait(NULL);
	pid = here_doc_f(fd, mini, pipe_fd);
	if (pid == 0)
		here_doc_extra(cmd, fd, mini, pipe_fd);
	wait(NULL);
	close(fd[1]);
	return (fd[0]);
}

int	check_here_doc(char **cmd, int j)
{
	while (j >= 2)
	{
		if (check_in_type(cmd[j]) == 2)
			return (1);
		j--;
	}
	return (0);
}
