/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_util3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:51:37 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/06/20 14:56:52 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	between_state(int state)
{
	if (state == 0)
		state = 1;
	else
		state = 0;
	return (state);
}

void	empty_line(char *command1, t_minishell *mini)
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
	if (command_s[0] == NULL)
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

char	*tab_to_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] >= 9 && cmd[i] <= 13)
			cmd[i] = ' ';
		i++;
	}
	return (cmd);
}

int	between_extra(char *cmd, int i0, int i1, int i2)
{
	if (i2 == 1)
		return (1);
	if (i1 == 2 && cmd[i0] == '\"')
		return (0);
	if (i1 == 1 && cmd[i0] == '\'')
		return (0);
	return (1);
}

void	sing_exit(t_minishell *mini)
{
	if (g_signal_var == -2)
		return (free_mini(mini), exit(130));
	if (mini->temp[1] == -1)
		return (free_mini(mini), exit(127));
	else if (mini->temp[1] == 1)
		return (free_mini(mini), exit(1));
	return (free_mini(mini), exit(0));
}
