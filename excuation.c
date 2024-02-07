/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excuation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 23:20:37 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/02/07 22:23:54 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **var)
{
	int	i;

	i = 0;
	while (var[i] != NULL)
	{
		free(var[i]);
		i++;
	}
	free(var);
}

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*create_command(char *command, char *path)
{
	char	*full_command;
	char	*full_command2;
	char	**args;
	int		i;

	args = ft_split(path, ':');
	if (!args)
		return (NULL);
	i = 0;
	while (args[i] != NULL)
	{
		full_command = ft_strjoin(args[i], "/");
		if (!full_command)
			return (free_split(args), NULL);
		full_command2 = full_command;
		full_command = ft_strjoin(full_command, command);
		if (!full_command)
			return (free(full_command2), free_split(args), NULL);
		free(full_command2);
		if (access(full_command, X_OK) == 0)
			return (free_split(args), full_command);
		free(full_command);
		i++;
	}
	return (free_split(args), NULL);
}

int	excute_command(char **argv, char **envp, int x)
{
	char	**command;
	char	*command1;

	command = ft_split(argv[x], ' ');
	command1 = create_command(command[0], find_path(envp));
	if (command1 == NULL)
	{
		ft_putstr_fd("Error: Unknown Command\n", 2);
		free_split(command);
		free(command1);
		free_split(argv);
		return (-1);
	}
	if (execve(command1, command, envp) == -1)
	{
		ft_putstr_fd("Error: Command unable to excute\n", 2);
		free_split(command);
		free(command1);
	}
	return (-1);
}

int	excute_command_d(char *cmd, char **envp)
{
	char	**command;
	char	*command1;

	command = ft_split(cmd, ' ');
	command1 = create_command(command[0], find_path(envp));
	if (command1 == NULL)
	{
		ft_putstr_fd("Error: Unknown Command\n", 2);
		free_split(command);
		free(command1);
		return (-1);
	}
	if (execve(command1, command, envp) == -1)
	{
		ft_putstr_fd("Error: Command unable to excute\n", 2);
		free_split(command);
		free(command1);
	}
	return (-1);
}
