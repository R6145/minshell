/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excuationiv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:43:43 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/03/27 13:53:36 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	excute_command_d(char *cmd, t_minishell *mini)
{
	char	**command;
	char	*command1;

	cmd = env_handling(cmd, mini);
	cmd = cleanup_quotes(cmd);
	command = ft_split(cmd, ' ');
	free(cmd);
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
		j--;
	}
	names[i] = NULL;
	return (names);
}

int	here_doc_extra(char *cmd, int fd[2], t_minishell *mini, int **pipe_fd)
{
	int		i;
	char	**names;

	i = 0;
	close(fd[0]);
	names = here_maker(cmd);
	i = amount_of_arg(names) - 1;
	while (i >= 0)
	{
		cmd = readline(">");
		if (ft_strncmp(cmd, names[i], ft_strlen(names[i])) == 0)
		{
			if (i == 0)
				break ;
			i--;
		}
		write(fd[1], cmd, ft_strlen(cmd));
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	free_split(names);
	free_mini(mini);
	close_pipe(pipe_fd, mini->temp[1]);
	free_pipe(pipe_fd);
	exit(0);
}

pid_t	here_doc_f(int fd[2], t_minishell *mini, int **pipe_fd)
{
	pid_t	pid;

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
	return (pid);
}

int	here_doc(char *cmd, t_minishell *mini, int **pipe_fd)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Pipe failed\n", 2);
		free_mini(mini);
		return (close_pipe(pipe_fd, mini->temp[1]), free_pipe(pipe_fd), exit(5),
			0);
	}
	wait(NULL);
	pid = here_doc_f(fd, mini, pipe_fd);
	if (pid == 0)
		here_doc_extra(cmd, fd, mini, pipe_fd);
	wait(NULL);
	close(fd[1]);
	return (fd[0]);
}

int	check_here_doc(char **cmd, int j)
{
	while (j >= 2)
	{
		if (check_in_type(cmd[j]) == 2)
			return (1);
		j--;
	}
	return (0);
}

int	excuate(char **command, char *command1, t_minishell *mini)
{
	int	x;

	x = 0;
	if ((ft_strncmp(command1, "/usr/bin/env", 12) == 0))
		print_env(mini->envps);
	else if (ft_strncmp(command1, "export", 7) == 0)
		add_env(mini->envps, command[1]);
	else if (ft_strncmp(command1, "unset", 6) == 0)
		remove_env(mini->envps, command[1]);
	else if (ft_strncmp(command1, "/usr/bin/pwd", 12) == 0)
		get_pwd();
	else if (ft_strncmp(command1, "cd", 3) == 0)
		x = cd(mini->envps, command[1]);
	else if (ft_strncmp(command1, "/usr/bin/echo", 13) == 0)
		echo(command);
	return (x);
}

int	excuate_s(char *command1, char **env)
{
	char	*command;
	char	*command2;
	char	**command_s;
	int		x;

	x = 0;
	command = cleanup_input(command1);
	command2 = command;
	create_dumby_files(command, NULL, NULL);
	command = cleanup_output(command);
	free(command2);
	command2 = command;
	command = cleanup_quotes(command1);
	free(command2);
	command_s = ft_split(command, ' ');
	if (ft_strncmp(command_s[0], "export", 7) == 0)
		add_env(env, command_s[1]);
	else if (ft_strncmp(command_s[0], "unset", 6) == 0)
		remove_env(env, command_s[1]);
	else if (ft_strncmp(command_s[0], "cd", 3) == 0)
		x = cd(env, command_s[1]);
	free(command);
	free_split(command_s);
	return (x);
}

void	exiting(char *command1, t_minishell *mini)
{
	char	*command;
	char	*command2;
	char	**command_s;

	command = cleanup_input(command1);
	command2 = command;
	create_dumby_files(command, NULL, NULL);
	command = cleanup_output(command);
	free(command2);
	command_s = ft_split(command, ' ');
	if (ft_strncmp(command_s[0], "exit", 5) == 0)
	{
		free(command);
		free(command1);
		free_split(command_s);
		free_mini(mini);
		exit(0);
	}
	free(command);
	free_split(command_s);
}

char	*rp_cmd(char *cmd, char *key, char *des, int j)
{
	int		i;
	int		z;
	char	*cmd1;

	i = 0;
	z = 0;
	cmd1 = malloc(sizeof(char) * (ft_strlen(cmd) + ft_strlen(des) + 2));
	while (i < j)
	{
		cmd1[i] = cmd[i];
		i++;
	}
	j = i + ft_strlen(key) + 1;
	while (des[z] != '\0')
		cmd1[i++] = des[z++];
	while (cmd[j] != '\0')
		cmd1[i++] = cmd[j++];
	cmd1[i] = '\0';
	free(cmd);
	cmd = cmd1;
	return (cmd1);
}

char	*rp_cmd_emp(char *cmd, char *key, int j)
{
	int		i;
	char	*cmd1;

	i = 0;
	cmd1 = malloc(sizeof(char) * (ft_strlen(cmd) + 2));
	while (i < j)
	{
		cmd1[i] = cmd[i];
		i++;
	}
	j = i + ft_strlen(key) + 1;
	while (cmd[j] != '\0')
		cmd1[i++] = cmd[j++];
	cmd1[i] = '\0';
	free(cmd);
	cmd = cmd1;
	return (cmd1);
}

char	*enved_cmd(char *cmd, char *cmd1, int j, t_minishell *mini)
{
	int		i;
	char	*key_env;

	i = 0;
	if (ft_strncmp(cmd1, "?", 5) == 0)
	{
		key_env = ft_itoa(mini->exit_status);
		cmd = rp_cmd(cmd, "?", key_env, j);
		return (free(key_env), (cmd));
	}
	while (mini->envps[i] != NULL)
	{
		key_env = env_key(mini->envps[i]);
		if (ft_strncmp(cmd1, key_env, ft_strlen(key_env) + 2) == 0)
		{
			cmd = rp_cmd(cmd, key_env, mini->envps[i] + ft_strlen(key_env) + 1,
				j);
			free(key_env);
			return (cmd);
		}
		free(key_env);
		i++;
	}
	cmd = rp_cmd_emp(cmd, cmd1, j);
	return (cmd);
}

char	*env_handling(char *cmd, t_minishell *mini)
{
	int		i;
	int		j;
	char	*cmd_cleaned;

	i = 0;
	j = 0;
	cmd_cleaned = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	while ((int)ft_strlen(cmd) >= j && cmd[j] != '\0')
	{
		i = 0;
		if (cmd[j] == '$' && between_sq(cmd, j) == 0)
		{
			j++;
			while (cmd[j] != ' ' && cmd[j] != '\0' && cmd[j] != '\"'
				&& cmd[j] != '\'')
			{
				cmd_cleaned[i++] = cmd[j++];
			}
			cmd_cleaned[i] = '\0';
			cmd = enved_cmd(cmd, cmd_cleaned, j - i - 1, mini);
		}
		j++;
	}
	free(cmd_cleaned);
	return (cmd);
}

char	*cleanup_quotes(char *cmd)
{
	int		i;
	int		j;
	char	*cmd1;

	i = 0;
	j = 0;
	cmd1 = malloc(sizeof(char) * (ft_strlen(cmd) + 2));
	while (cmd[j] != '\0')
	{
		if (cmd[j] != '\"' && cmd[j] != '\'')
			cmd1[i++] = cmd[j];
		else if ((cmd[j] == '\"' || cmd[j] == '\'') && between(cmd, j) == 0)
			cmd1[i++] = cmd[j];
		j++;
	}
	cmd1[i] = '\0';
	free(cmd);
	return (cmd1);
}

int	between_sq(char *cmd, int j)
{
	int	i;
	int	state;
	int	state2;

	i = 0;
	state = 0;
	state2 = 0;
	while (cmd[i] != '\0' && i <= j)
	{
		if (cmd[i] == '\"')
			state++;
		if (cmd[i] == '\'')
		{
			if (state % 2 == 0 && state2 != 1)
				state2 = 1;
			else
				state2 = 0;
		}
		i++;
	}
	return (state2);
}

int	between(char *cmd, int j)
{
	int	i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	while (cmd[i[0]] != '\0' && i[0] <= j)
	{
		if (cmd[i[0]] == '\"')
			i[1] = between_state(i[1]);
		if (cmd[i[0]] == '\'')
			i[2] = between_state(i[2]);
		if (cmd[i[0]] == '\'' || cmd[i[0]] == '\"')
			i[3]++;
		if (i[0] == j)
		{
			if (i[3] != 1 && (i[2] == 1 || i[1] == 1))
				return (0);
			return (1);
		}
		if (i[1] == 0 && i[2] == 0)
			i[3] = 0;
		i[0]++;
	}
	return (05);
}

int	between_state(int state)
{
	if (state == 0)
		state = 1;
	else
		state = 0;
	return (state);
}
