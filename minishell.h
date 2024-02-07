/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:12:56 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/02/07 22:41:11 by fmaqdasi         ###   ########.fr       */
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
	int		number_of_commands;
}			t_minishell;

// parscing
char		**cut_commands(char *line);
int			asign_command(char **commands, char *line, int *pos, int amount);
int			amount_of_commands(char *line);
int			*cut_pos(char *line);
int			between_quo(char *line, int x);
void		between_quo_extra(char line, int *flag, int *flag2, char s);
// freeing functions
void		freeall(char **st, int j);
// excucation
void		free_split(char **var);
char		*find_path(char **envp);
char		*create_command(char *command, char *path);
int			excute_command(char **argv, char **envp, int x);
int			excute_command_d(char *cmd, char **envp);
pid_t		forking(int **fd, int argc);
int			**fd_create(int argc);
void		piping(int **x, int argc);
void		close_pipe(int **fd, int argc);
void		free_pipe(int **fd);
void		child(char **argv, char **envp, int **pipe_fd, int i[2]);
void		middle_child(char **argv, char **envp, int **pipe_fd, int i[2]);
void		middle(char **argv, char **envp, int **pipe_fd, int i[2]);
void		parent(char **argv, char **envp, int **pipe_fd, int i);
int			pipex(int argc, char **argv, char **envp);
char		**create_spilt_commands(char **cmd, int cmd_num);

#endif