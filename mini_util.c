/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:07:04 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/03/24 20:53:36 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inti(t_minishell *mini)
{
	// int	i;
	// i = 0;
	mini->number_of_commands = -1;
	mini->commands = NULL;
	// while (i < MAX_COMMANDS)
	// {
	// 	mini->input[i] = -1;
	// 	mini->inp_type[i] = -1;
	// 	mini->output[i] = -1;
	// 	mini->out_type[i] = -1;
	// 	i++;
	// }
	mini->temp[0] = -1;
	mini->temp[1] = -1;
	mini->temp[2] = -1;
	mini->exit_status = 0;
}
