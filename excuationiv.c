/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excuationiv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:43:43 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/03/12 17:17:42 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	excute_command_d(char *cmd, char **envp) // outdated
{
	char **command;
	char *command1;

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
		if (check_in_type(argv[mini->temp[0] - 1]) == 1)
		{
			fd = open(file, O_RDONLY);
			free(file);
			temp = argv[mini->temp[0] - 1];
			argv[mini->temp[0] - 1] = cleanup_input(argv[mini->temp[0] - 1]);
			free(temp);
		}
		else
		{
			free(file);
			fd = here_doc(argv[mini->temp[0] - 1], mini, pipe_fd);
			temp = argv[mini->temp[0] - 1];
			argv[mini->temp[0] - 1] = cleanup_input(argv[mini->temp[0] - 1]);
			free(temp);
		}
	}
	else
		fd = open(argv[mini->temp[0] - 2], O_RDONLY);
	if (fd == -1)
		free_error_fd(pipe_fd, mini);
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
	int	i;

	i = ft_strlen(cmd);
	while (i >= 0)
	{
		if (cmd[i] == '>' && between_quo(cmd, i) == 0)
		{
			i--;
			if (i >= 0 && cmd[i] == '>')
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
	int	i;

	i = ft_strlen(cmd);
	while (i >= 0)
	{
		if (cmd[i] == '<' && between_quo(cmd, i) == 0)
		{
			i--;
			if (i >= 0 && cmd[i] == '<')
				return (2);
			else
				return (1);
		}
		i--;
	}
	return (0);
}

void	create_dumby_files(char *cmd, int **pipe_fd, t_minishell *mini)
{
	int		i;
	int		j;
	int		x;
	char	*file_name;

	i = ft_strlen(cmd);
	while (i >= 0)
	{
		j = 0;
		if (cmd[i] == '>' && between_quo(cmd, i) == 0)
		{
			x = i + 1;
			file_name = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
			while (cmd[x] == ' ')
				x++;
			while (cmd[x] != ' ' && cmd[x] != '\0')
				file_name[j++] = cmd[x++];
			file_name[j] = '\0';
			i = create_file_dumb(file_name, cmd, i);
			if (i == -1)
				free_error_fd(pipe_fd, mini);
			free(file_name);
		}
		i--;
	}
}

int	create_file_dumb(char *cmd_name, char *cmd, int i)
{
	int	fd;

	if (i > 0 && cmd[i - 1] == '>')
	{
		i--;
		fd = open(cmd_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else
		fd = open(cmd_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		return (-1);
	}
	close(fd);
	return (i);
}

char	*get_filename_pos(char *cmd, int i)
{
	int		j;
	char	*file_name;

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

char	**here_maker(char *cmd)
{
	int		i;
	int		j;
	char	**names;

	i = 0;
	j = ft_strlen(cmd) - 1;
	names = malloc(sizeof(char *) * (j + 2));
	while (j >= 0)
	{
		if (cmd[j] == '<' && between_quo(cmd, j) == 0)
		{
			j--;
			if (cmd[j] == '<')
				names[i++] = get_filename_pos(cmd, j + 1);
		}
	}
	j--;
	names[i] = NULL;
	return (names);
}

int	here_doc(char *cmd, t_minishell *mini, int **pipe_fd)
{
	pid_t	pid;
	int		fd[2];
	int		i;
	char	**names;

	i = 0;
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Pipe failed\n", 2);
		free_mini(mini);
		return (close_pipe(pipe_fd, mini->temp[1]), free_pipe(pipe_fd), exit(5),
			0);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Fork failed\n", 2);
		close(fd[1]);
		close(fd[0]);
		free_mini(mini);
		return (close_pipe(pipe_fd, mini->temp[1]), free_pipe(pipe_fd), exit(5),
			0);
	}
	if (pid == 0)
	{
		close(fd[0]);
		names = here_maker(cmd);
		i = amount_of_arg(names) - 1;
		while (i >= 0)
		{
			write(2, "here\n", 5);
			cmd = readline(">");
			if (ft_strncmp(cmd, names[i], ft_strlen(names[i])) == 0)
			{
				if (i == 0)
					break ;
				exit(12);
				i--;
			}
			write(fd[1], cmd, ft_strlen(cmd));
		}
		close(fd[1]);
		free_split(names);
		free_mini(mini);
		close_pipe(pipe_fd, mini->temp[1]);
		free_pipe(pipe_fd);
		exit(0);
	}
	wait(NULL);
	close(fd[1]);
	return (fd[0]);
}
