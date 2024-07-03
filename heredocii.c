/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:21:01 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/07/03 10:48:28 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_heredoc(char **names, int fd[2], t_minishell *mini, int **pipe_fd)
{
	if (mini->tempc != NULL)
		free(mini->tempc);
	return ((close(fd[1]), close(fd[0]), free_split(names), free_mini(mini),
			close_pipe(pipe_fd, mini->temp[1])), free_pipe(pipe_fd), 0);
}
