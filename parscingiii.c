/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parscingiii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:55:08 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/02/09 20:28:32 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_ipop(t_minishell *mini, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		check_for_ipop2(mini, cmd, i);
		i++;
	}
}

void	check_for_ipop2(t_minishell *mini, char **cmd, int i)
{
	int		j;
	char	**line;

	j = 0;
	line = ft_split(cmd[i], ' ');
	while (line[j] != NULL)
	{
		ipop_type(mini, line[j], j, i);
		j++;
	}
	free_split(line);
}

void	ipop_type(t_minishell *mini, char *line, int j, int i)
{
	if (ft_strncmp(line, "<", 1) == 0)
	{
		mini->input[i] = j;
		mini->inp_type[i] = 1;
	}
	else if (ft_strncmp(line, "<<", 2) == 0)
	{
		mini->input[i] = j;
		mini->inp_type[i] = 2;
	}
	else if (ft_strncmp(line, ">", 1) == 0)
	{
		mini->output[i] = j;
		mini->out_type[i] = 1;
	}
	else if (ft_strncmp(line, "<<", 2) == 0)
	{
		mini->output[i] = j;
		mini->out_type[i] = 2;
	}
}
