/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanupio.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:38:52 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/06/10 16:34:42 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_minishell *mini, char **argv, int **pipe_fd)
{
	int		fd;
	char	*file;
	char	*temp;

	file = get_filename(argv[mini->temp[0] - 1]);
	if (file != NULL)
	{
		if (check_in_type(argv[mini->temp[0] - 1]) == 1)
		{
			fd = open(file, O_RDONLY);
			free(file);
			temp = argv[mini->temp[0] - 1];
			argv[mini->temp[0] - 1] = cleanup_input(argv[mini->temp[0] - 1]);
			free(temp);
		}
		else
			fd = here_docking(file, argv, mini, pipe_fd);
	}
	else
		fd = open(argv[mini->temp[0] - 2], O_RDONLY);
	if (fd == -1)
		free_error_fd(pipe_fd, mini);
	return (fd);
}

int	here_docking(char *file, char **argv, t_minishell *mini, int **pipe_fd)
{
	int		fd;
	char	*temp;

	fd = 0;
	free(file);
	fd = here_doc(argv[mini->temp[0] - 1], mini, pipe_fd);
	temp = argv[mini->temp[0] - 1];
	argv[mini->temp[0] - 1] = cleanup_input(argv[mini->temp[0] - 1]);
	free(temp);
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
