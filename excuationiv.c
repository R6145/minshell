/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excuationiv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:43:43 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/02/20 17:50:20 by fmaqdasi         ###   ########.fr       */
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
	char	*temp;

	file = get_filename(argv[mini->temp[0] - 1]);
	if (file != NULL)
	{
		fd = open(file, O_RDONLY);
		free(file);
		temp = argv[mini->temp[0] - 1];
		argv[mini->temp[0] - 1] = cleanup_input(argv[mini->temp[0] - 1]);
		free(temp);
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

char	*cleanup_input(char *cmd)
{
	int		i;
	int		j;
	char	*cmd_cleaned;

	i = 0;
	j = 0;
	cmd_cleaned = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	while (cmd[j] != '\0')
	{
		if (cmd[j] == '<' && between_quo(cmd, i) == 0)
		{
			j++;
			if (cmd[j] == '<')
				j++;
			while (cmd[j] == ' ')
				j++;
			while (cmd[j] != ' ' && cmd[j] != '\0')
				j++;
		}
		else
			cmd_cleaned[i++] = cmd[j++];
	}
	cmd_cleaned[i] = '\0';
	return (cmd_cleaned);
}

char	*get_filename(char *cmd)
{
	int		i;
	int		j;
	char	*file_name;

	i = ft_strlen(cmd);
	j = 0;
	while (i >= 0)
	{
		if (cmd[i] == '<' && between_quo(cmd, i) == 0)
		{
			i++;
			file_name = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
			while (cmd[i] == ' ')
				i++;
			while (cmd[i] != ' ' && cmd[i] != '\0')
			{
				file_name[j++] = cmd[i++];
			}
			file_name[j] = '\0';
			return (file_name);
		}
		i--;
	}
	return (NULL);
}

char	*cleanup_output(char *cmd)
{
	int		i;
	int		j;
	char	*cmd_cleaned;

	i = 0;
	j = 0;
	cmd_cleaned = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	while (cmd[j] != '\0')
	{
		if (cmd[j] == '>' && between_quo(cmd, i) == 0)
		{
			j++;
			if (cmd[j] == '>')
				j++;
			while (cmd[j] == ' ')
				j++;
			while (cmd[j] != ' ' && cmd[j] != '\0')
				j++;
		}
		else
			cmd_cleaned[i++] = cmd[j++];
	}
	cmd_cleaned[i] = '\0';
	return (cmd_cleaned);
}

char	*get_filename_out(char *cmd)
{
	int		i;
	int		j;
	char	*file_name;

	i = ft_strlen(cmd);
	j = 0;
	while (i >= 0)
	{
		if (cmd[i] == '>' && between_quo(cmd, i) == 0)
		{
			i++;
			file_name = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
			while (cmd[i] == ' ')
				i++;
			while (cmd[i] != ' ' && cmd[i] != '\0')
			{
				file_name[j++] = cmd[i++];
			}
			file_name[j] = '\0';
			return (file_name);
		}
		i--;
	}
	return (NULL);
}

int	check_out_type(char *cmd)
{
	int		i;

	i = ft_strlen(cmd);
	while (i >= 0)
	{
		if (cmd[i] == '>' && between_quo(cmd, i) == 0)
		{
			i--;
			if (cmd[i] == '>')
				return (2);
			else
				return (1);
		}
		i--;
	}
	return (0);
}

int	check_in_type(char *cmd)
{
	int		i;

	i = ft_strlen(cmd);
	while (i >= 0)
	{
		if (cmd[i] == '>' && between_quo(cmd, i) == 0)
		{
			i--;
			if (cmd[i] == '>')
				return (2);
			else
				return (1);
		}
		i--;
	}
	return (0);
}
