/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excuationiv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:43:43 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/06/24 17:17:15 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	excute_command_d(char *cmd, t_minishell *mini)
{
	char	**command;
	char	*command1;

	command1 = NULL;
	cmd = env_handling(cmd, mini);
	cmd = cleanup_quotes(cmd);
	command = ft_split(cmd, ' ');
	free(cmd);
	if (command[0] == NULL)
		return (free_split(command), (-1));
	command1 = create_command(command[0], find_path(mini->envps));
	if (command1 == NULL && check_cmd(command[0]) == 0)
		return (ft_putstr_fd("Error: Unknown Command\n", 2),
			free_split(command), free(command1), (-1));
	if (check_cmd(command[0]) == 1)
	{
		mini->temp[0] = excuate(command, command[0], mini);
		return (free(command1), free_split(command), mini->temp[0]);
	}
	if (execve(command1, command, mini->envps) == -1)
		ft_putstr_fd("Error: Command unable to excute\n", 2);
	return (free_split(command), free(command1), (-1));
}

void	single_command(char *argv, t_minishell *mini)
{
	char	*file;
	char	*temp;

	temp = argv;
	file = get_filename(argv);
	if (file != NULL)
	{
		mini->tempc = file;
		temp = input_code_s(file, argv, NULL, mini);
		if (mini->temp[0] == -1)
			return (free(file), free_error_fd(NULL, mini), exit(14));
		free(file);
	}
	else
		mini->temp[0] = open("/dev/tty", O_RDONLY);
	mini->temp[2] = dup2(mini->temp[0], STDIN_FILENO);
	close(mini->temp[0]);
	temp = create_dumbf_outs(temp, mini);
	mini->temp[1] = excute_command_d(temp, mini);
	sing_exit(mini);
}

int	excuate(char **command, char *command1, t_minishell *mini)
{
	int	x;

	x = 0;
	if ((ft_strncmp(command1, "/usr/bin/env", 12) == 0))
		print_env(mini->envps);
	else if (ft_strncmp(command1, "export", 7) == 0)
		add_remove_all_env(mini->envps, command, 0, mini);
	else if (ft_strncmp(command1, "unset", 6) == 0)
		add_remove_all_env(mini->envps, command, 1, mini);
	else if (ft_strncmp(command1, "/usr/bin/pwd", 12) == 0
		|| ft_strncmp(command1, "pwd", 4) == 0)
		get_pwd();
	else if (ft_strncmp(command1, "cd", 3) == 0)
		x = cd(mini->envps, command);
	else if (ft_strncmp(command1, "/usr/bin/echo", 13) == 0
		|| ft_strncmp(command1, "echo", 5) == 0)
		echo(command);
	return (x);
}

int	excuate_s(char *command1, char **env, t_minishell *mini)
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
		x = add_remove_all_env(env, command_s, 0, mini);
	else if (ft_strncmp(command_s[0], "unset", 6) == 0)
		add_remove_all_env(env, command_s, 1, mini);
	else if (ft_strncmp(command_s[0], "cd", 3) == 0)
		x = cd(env, command_s);
	free(command);
	free_split(command_s);
	return (x);
}

void	excute_code(char **argv, int **pipe_fd, t_minishell *mini, int x)
{
	int	y;

	y = excute_command(argv, mini, x);
	if (g_signal_var == -2)
		return (free_mini(mini), exit(1));
	else if (mini->exit_status == 150)
		return (free_mini(mini), free_pipe(pipe_fd), exit(0));
	else if (y == -1)
		return (free_mini(mini), free_pipe(pipe_fd), exit(127));
	else if (y == 1)
		return (free_mini(mini), free_pipe(pipe_fd), exit(1));
	return (free_mini(mini), free_pipe(pipe_fd), exit(0));
}
