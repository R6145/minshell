/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:00:55 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/04/07 19:56:56 by fmaqdasi         ###   ########.fr       */
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
