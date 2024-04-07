/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_util3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:51:37 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/04/07 19:59:00 by fmaqdasi         ###   ########.fr       */
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
