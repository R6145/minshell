/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parscingiii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:55:08 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/03/23 16:09:28 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	check_for_ipop(t_minishell *mini, char **cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i] != NULL)
// 	{
// 		check_for_ipop2(mini, cmd, i);
// 		i++;
// 	}
// }

// void	check_for_ipop2(t_minishell *mini, char **cmd, int i)
// {
// 	int		j;
// 	char	**line;

// 	j = 0;
// 	line = ft_split(cmd[i], ' ');
// 	while (line[j] != NULL)
// 	{
// 		ipop_type(mini, line[j], j, i);
// 		j++;
// 	}
// 	free_split(line);
// }

// void	ipop_type(t_minishell *mini, char *line, int j, int i)
// {
// 	if (ft_strncmp(line, "<", 1) == 0)
// 	{
// 		mini->input[i] = j;
// 		mini->inp_type[i] = 1;
// 	}
// 	else if (ft_strncmp(line, "<<", 2) == 0)
// 	{
// 		mini->input[i] = j;
// 		mini->inp_type[i] = 2;
// 	}
// 	else if (ft_strncmp(line, ">", 1) == 0)
// 	{
// 		mini->output[i] = j;
// 		mini->out_type[i] = 1;
// 	}
// 	else if (ft_strncmp(line, ">>", 2) == 0)
// 	{
// 		mini->output[i] = j;
// 		mini->out_type[i] = 2;
// 	}
// }

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
