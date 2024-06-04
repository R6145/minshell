/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parscingiii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:55:08 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/06/04 19:51:39 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "/usr/bin/env", 12) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "/usr/bin/echo", 13) == 0)
		return (1);
	return (0);
}

int	check_cmd2(char *cmd)
{
	char	*command;
	char	*command2;
	char	**command_s;

	command = cleanup_input(cmd);
	command2 = command;
	command = cleanup_output(command);
	free(command2);
	command_s = ft_split(command, ' ');
	if (command_s[0] == NULL)
		return (free(command), free_split(command_s), 0);
	if (ft_strncmp(command_s[0], "export", 7) == 0)
		return (free(command), free_split(command_s), 1);
	if (ft_strncmp(command_s[0], "unset", 6) == 0)
		return (free(command), free_split(command_s), 1);
	if (ft_strncmp(command_s[0], "exit", 6) == 0)
		return (free(command), free_split(command_s), 1);
	if (ft_strncmp(command_s[0], "cd", 6) == 0)
		return (free(command), free_split(command_s), 1);
	return (free(command), free_split(command_s), 0);
}
