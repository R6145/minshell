/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parscingii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:52:53 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/02/09 20:18:53 by fmaqdasi         ###   ########.fr       */
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
	sep[amount] = NULL;
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

char	**create_pipex_commands(char **cmd, int cmd_num)
{
	int		i;
	int		j;
	char	**cmd2;

	i = 2;
	j = 0;
	cmd2 = (char **)malloc(sizeof(char *) * (cmd_num + 4));
	cmd2[0] = (char *)malloc(sizeof(char) * 6);
	ft_strlcpy(cmd2[0], "pipex", 6);
	cmd2[1] = (char *)malloc(sizeof(char) * 10);
	ft_strlcpy(cmd2[1], "/dev/tty", 10);
	while (i <= cmd_num + 1)
	{
		cmd2[i] = (char *)malloc(sizeof(char) * (ft_strlen(cmd[j]) + 1));
		ft_strlcpy(cmd2[i], cmd[j], ft_strlen(cmd[j]) + 1);
		j = j + 2;
		i++;
	}
	cmd2[i] = (char *)malloc(sizeof(char) * 10);
	ft_strlcpy(cmd2[i++], "/dev/tty", 10);
	cmd2[i] = NULL;
	return (cmd2);
}

int	amount_of_arg(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		i++;
	}
	return (i);
}
