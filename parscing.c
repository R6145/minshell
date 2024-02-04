/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parscing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:35:25 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/02/04 22:36:21 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	amount_of_commands(char *line)
{
	int	amount;
	int	is_command;
	int	i;

	is_command = 0;
	amount = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == ';' || line[i] == '|') && (between_quo(line, i) == 0))
		{
			is_command = 0;
			amount++;
		}
		else if (!is_command)
		{
			is_command = 1;
			amount++;
		}
		i++;
	}
	return (amount);
}

int	*cut_pos(char *line)
{
	int	i;
	int	j;
	int	*x;

	x = (int *)malloc(sizeof(int) * (ft_strlen(line) + 1));
	if (x == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == ';' || line[i] == '|') && (between_quo(line, i) == 0))
		{
			x[j] = i;
			j++;
		}
		i++;
	}
	x[j] = -1;
	return (x);
}

int	between_quo(char *line, int x)
{
	int		i;
	int		flag;
	int		flag2;
	char	s;

	i = 0;
	flag = 0;
	flag2 = 0;
	while (line[i] != '\0')
	{
		if (flag == 0 && (line[i] == '"' || line[i] == 39))
		{
			s = line[i];
			flag = 1;
		}
		else if (flag == 1 && (line[i] == '"' || line[i] == 39))
		{
			between_quo_extra(line[i], &flag, &flag2, s);
		}
		if (i == x)
			return (flag);
		i++;
	}
	return (0);
}

void	between_quo_extra(char line, int *flag, int *flag2, char s)
{
	if (line != s && *flag2 == 0)
	{
		*flag2 = 1;
	}
	else if (line != s && *flag2 == 1)
	{
		*flag2 = 0;
	}
	else
		*flag = 0;
}
