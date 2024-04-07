/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:54:51 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/04/07 19:57:07 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_check(char *cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < (int)ft_strlen(cmd) && cmd[i] != '\0')
	{
		if (cmd[i] != '\0' && cmd[i] != '>' && cmd[i] != '<' && cmd[i] != '|'
			&& cmd[i] != ' ')
			flag = 1;
		if (cmd[i] == '|')
		{
			i++;
			if (flag == 0)
				return (1);
			while (cmd[i] == ' ' || cmd[i] == '>' || cmd[i] == '<')
				i++;
			if (cmd[i] == '\0' || cmd[i] == '|')
				return (1);
			flag = 0;
		}
		i++;
	}
	return (0);
}

int	error_checker(char *cmd)
{
	if (check_dq(cmd) != 0)
		return (ft_putstr_fd("Missing quote", 2), (1));
	if (check_sq(cmd) != 0)
		return (ft_putstr_fd("Missing quote", 2), (2));
	if (redir_check(cmd) != 0)
		return (ft_putstr_fd("Missing arguement", 2), (3));
	if (redir_check2(cmd) != 0)
		return (ft_putstr_fd("Wrong no of > ot <", 2), (4));
	if (redir_check3(cmd) != 0)
		return (ft_putstr_fd("Wrong no of > ot <", 2), (5));
	if (pipe_check(cmd) != 0)
		return (ft_putstr_fd("pipe argument missing", 2), (6));
	return (0);
}

void	free_mini(t_minishell *mini)
{
	if (mini == NULL)
		return ;
	if (mini->commands != NULL)
		free_split(mini->commands);
	free_split(mini->envps);
}

void	free_error_fd(int **pipe_fd, t_minishell *mini)
{
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
	free_mini(mini);
	return (close_pipe(pipe_fd, mini->temp[1]), free_pipe(pipe_fd), exit(1));
}

void	free_error_dup(int **pipe_fd, t_minishell *mini, int fd)
{
	free_mini(mini);
	ft_putstr_fd("Dup Error\n", 2);
	close(fd);
	return (close_pipe(pipe_fd, mini->temp[1]), free_pipe(pipe_fd), exit(4));
}
