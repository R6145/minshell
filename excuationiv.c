/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excuationiv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:43:43 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/02/18 22:21:59 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	open_file(t_minishell *mini, char **argv, int **pipe_fd)
{
	int		fd;
	char	*file;

	if (mini->input[mini->temp[0] - 3] != -1) // wrong
	{
		file = get_filename(mini, argv);
		fd = open(file, O_RDONLY);
		free(file);
	}
	else
		fd = open(argv[mini->temp[0] - 2], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		close_pipe(pipe_fd, mini->temp[1]);
		return (free_pipe(pipe_fd), exit(3), 0);
	}
	return (fd);
}

char	*get_filename(t_minishell *mini, char **argv)
{
	char	**arguments;
	char	*filename;
	int		i;

	arguments = ft_split(argv[mini->temp[0] - 1], ' ');
	i = amount_of_arg(arguments);
	while (i != 0)
	{
		if (ft_strncmp(arguments[i], "<", 2) == 0)
		{
			filename = ft_strdup(arguments[i + 1]);
			free_split(arguments);
			return (filename);
		}
		else if (ft_strncmp(arguments[i], "<<", 3) == 0)
		{
			// do here_doc
		}
		i--;
	}
	return (NULL);
}

void	cleanup_input(t_minishell *mini, char **argv)
{
	int		i;
	int		j;
	char	**arguments;

	i = 0;
	arguments = ft_split(argv[mini->temp[0] - 1], ' ');
	j = amount_of_arg(arguments);
	while (arguments[i] != NULL)
	{
		if (ft_strncmp(arguments[i], "<", 2) == 0 || ft_strncmp(arguments[i],
				"<<", 3) == 0)
		{
			free(arguments[i]);
			free(arguments[i + 1]);
			arguments[i] = NULL;
			arguments[i + 1] = NULL;
			i++;
		}
		i++;
	}
	free(argv[mini->temp[0] - 1]);
	argv[mini->temp[0] - 1] = rejoin_args(arguments, j);
	free_split(arguments);
}

char	*rejoin_args(char **argv, int amount)
{
	int		i;
	char	*args;
	char	*args2;

	i = 0;
	args = ft_strdup("");
	while (i < amount)
	{
		while (argv[i] == NULL && i < amount)
			i++;
		if (i >= amount)
			return (args);
		args2 = args;
		if (ft_strncmp(args, "", 1) == 0)
			args = ft_strjoin(args, argv[i]);
		else
		{
			args = ft_strjoin(args, " ");
			free(args2);
			args2 = args;
			args = ft_strjoin(args, argv[i]);
		}
		free(args2);
		i++;
	}
	return (args);
}
