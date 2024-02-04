/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:12:56 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/02/04 23:18:34 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_list2
{
	char	**commands;
	char	**envps;
}			t_Minishell;

char		**cut_commands(char *line);
int			asign_command(char **commands, char *line, int *pos, int amount);
void		freeall(char **st, int j);
int			amount_of_commands(char *line);
int			*cut_pos(char *line);
int			between_quo(char *line, int x);
void		between_quo_extra(char line, int *flag, int *flag2, char s);

#endif