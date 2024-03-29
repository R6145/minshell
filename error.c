/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:00:55 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/03/29 21:37:00 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dq(char *cmd)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\"' && between2(cmd, i) == 0)
			counter++;
		i++;
	}
	if (counter % 2 == 0)
		return (0);
	else
		return (1);
	return (0);
}

int	check_sq(char *cmd)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'' && between2(cmd, i) == 0)
			counter++;
		i++;
	}
	if (counter % 2 == 0)
		return (0);
	else
		return (1);
	return (0);
}

int	redir_check(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '>' && cmd[i + 1] == '>' && cmd[i + 2] == '>')
			return (1);
		if (cmd[i] == '<' && cmd[i + 1] == '<' && cmd[i + 2] == '<')
			return (1);
		i++;
	}
	return (0);
}

int	redir_check2(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '>')
		{
			i++;
			if (cmd[i] == '>')
				i++;
			while (cmd[i] == ' ')
				i++;
			if (cmd[i] == '\0' || cmd[i] == '>' || cmd[i] == '<'
				|| cmd[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	redir_check3(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '<')
		{
			i++;
			if (cmd[i] == '<')
				i++;
			while (cmd[i] == ' ')
				i++;
			if (cmd[i] == '\0' || cmd[i] == '>' || cmd[i] == '<'
				|| cmd[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

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
