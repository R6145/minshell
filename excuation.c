/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excuation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 23:20:37 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/03/26 16:45:04 by fmaqdasi         ###   ########.fr       */
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
	char	**args;
	int		i;

	full_command = NULL;
	args = ft_split(path, ':');
	if (!args)
		return (NULL);
	i = 0;
	while (args[i] != NULL)
	{
		full_command = create_command_extra(command, args[i]);
		if (full_command == NULL)
			return (free_split(args), NULL);
		if (access(full_command, X_OK) == 0)
			return (free_split(args), full_command);
		free(full_command);
		i++;
	}
	if (access(command, X_OK) == 0)
		return (free_split(args), ft_strdup(command));
	if (check_cmd(command))
		return (free_split(args), ft_strdup(command));
	return (free_split(args), NULL);
}

char	*create_command_extra(char *command, char *args)
{
	char	*full_command;
	char	*full_command2;

	full_command = ft_strjoin(args, "/");
	if (!full_command)
		return (NULL);
	full_command2 = full_command;
	full_command = ft_strjoin(full_command, command);
	if (!full_command)
		return (free(full_command2), NULL);
	free(full_command2);
	return (full_command);
}

int	excute_command(char **argv, t_minishell *mini, int x)
{
	char	**command;
	char	*command1;

	argv[x] = env_handling(argv[x], mini);
	command = ft_split(argv[x], ' ');
	command1 = create_command(command[0], find_path(mini->envps));
	if (command1 == NULL)
	{
		ft_putstr_fd("Error: Unknown Command\n", 2);
		return (free_split(command), free(command1), (-1));
	}
	if (check_cmd(command1) == 1)
	{
		mini->temp[0] = excuate(command, command1, mini);
		return (free(command1), free_split(command), mini->temp[0]);
	}
	if (execve(command1, command, mini->envps) == -1)
	{
		ft_putstr_fd("Error: Command unable to excute\n", 2);
		free_split(command);
		free(command1);
	}
	return (-1);
}
