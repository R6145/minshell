/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:07:04 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/04/07 19:49:21 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inti(t_minishell *mini)
{
	mini->number_of_commands = -1;
	mini->temp[0] = -1;
	mini->temp[1] = -1;
	mini->temp[2] = -1;
	mini->exit_status = 0;
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
