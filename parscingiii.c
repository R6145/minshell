/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parscingiii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:55:08 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/06/20 17:56:03 by fmaqdasi         ###   ########.fr       */
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
	else if (ft_strncmp(cmd, "/usr/bin/pwd", 12) == 0)
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

int	export_checker(char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!((argv[i][j] >= 48 && argv[i][j] <= 57) || argv[i][j] == '_'
					|| ft_isalpha(argv[i][j]) == 1 || argv[i][j] == '='))
				return (printf("%s Not a Valid Identifer\n", argv[i]), 0);
			if ((argv[i][j] >= 48 && argv[i][j] <= 57) && j == 0)
				return (printf("%s Not a Valid Identifer\n", argv[i]), 0);
			j++;
		}
		i++;
	}
	return (1);
}
