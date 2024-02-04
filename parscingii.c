/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parscingii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:52:53 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/02/04 23:20:15 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cut_commands(char *line)
{
	char	**sep;
	int		*pos;
	int		amount;

	pos = cut_pos(line);
	amount = amount_of_commands(line);
	sep = (char **)malloc(sizeof(char *) * (amount + 1));
	if (!sep)
		return (free(pos), NULL);
	if (asign_command(sep, line, pos, amount) == -1)
		return (free(pos), NULL);
	free(pos);
	return (sep);
}

int	asign_command(char **commands, char *line, int *pos, int amount)
{
	int	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (i[1] < amount)
	{
		if (pos[i[0]] != -1)
		{
			commands[i[1]++] = ft_substr(line, i[2], pos[i[0]] - i[2]);
			commands[i[1]] = ft_substr(line, pos[i[0]], 1);
			i[2] = i[2] + (pos[i[0]] - i[2]) + 1;
			i[0]++;
		}
		else
		{
			commands[i[1]] = ft_substr(line, i[2], ft_strlen(line) - i[2]);
		}
		i[1]++;
	}
	commands[i[1]] = NULL;
	return (0);
}

void	freeall(char **st, int j)
{
	while (j >= 0)
	{
		free(st[j]);
		j--;
	}
	free(st);
}
