/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:49:49 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/04/07 19:50:48 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	between2(char *cmd, int j)
{
	int	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (cmd[i[0]] != '\0' && i[0] <= j)
	{
		if (cmd[i[0]] == '\"' && i[2] == 0)
			i[1] = between_state(i[1]);
		if (cmd[i[0]] == '\'' && i[1] == 0)
			i[2] = between_state(i[2]);
		if (i[0] == j)
		{
			if (cmd[i[0]] == '\'' && i[1] == 1)
				return (1);
			else if (cmd[i[0]] == '\"' && i[2] == 1)
				return (1);
			else
				return (0);
		}
		i[0]++;
	}
	return (05);
}
