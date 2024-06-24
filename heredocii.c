/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:21:01 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/06/24 16:25:57 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_heredoc(char **names, int fd[2], t_minishell *mini, int **pipe_fd)
{
	return ((close(fd[1]), close(fd[0]), free_split(names), free_mini(mini),
			close_pipe(pipe_fd, mini->temp[1])), free_pipe(pipe_fd),
		free(mini->tempc), 0);
}
