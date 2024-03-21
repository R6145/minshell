/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:12:56 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/03/21 19:31:30 by fmaqdasi         ###   ########.fr       */
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

# define MAX_COMMANDS 1000

typedef struct s_list2
{
	char	**commands;
	char	**envps;
	int		number_of_commands;
	// int		input[1000];
	// int		inp_type[1000];
	// int		output[1000];
	// int		out_type[1000];
	int		temp[3];
}			t_minishell;

// minishell utills
void		inti(t_minishell *mini);
// parscing
char		**cut_commands(char *line);
int			asign_command(char **commands, char *line, int *pos, int amount);
int			amount_of_commands(char *line);
int			*cut_pos(char *line);
int			between_quo(char *line, int x);
void		between_quo_extra(char line, int *flag, int *flag2, char s);
int			amount_of_arg(char **cmd);
// void		check_for_ipop(t_minishell *mini, char **cmd);
// void		check_for_ipop2(t_minishell *mini, char **cmd, int i);
// void		ipop_type(t_minishell *mini, char *line, int j, int i);
// freeing functions
void		freeall(char **st, int j);
void		free_pipe(int **fd);
void		free_split(char **var);
// excucation
char		*find_path(char **envp);
char		*create_command(char *command, char *path);
char		*create_command_extra(char *command, char *args);
int			excute_command(char **argv, char **envp, int x);
int			excute_command_d(char *cmd, char **envp);
pid_t		forking(int **fd, int argc);
int			**fd_create(int argc);
void		piping(int **x, int argc);
void		close_pipe(int **fd, int argc);
void		child(char **argv, char **envp, int **pipe_fd, t_minishell *mini);
void		middle_child(char **argv, char **envp, int **pipe_fd,
				t_minishell *mini);
void		middle(char **argv, char **envp, int **pipe_fd, t_minishell *mini);
void		parent(char **argv, char **envp, int **pipe_fd, t_minishell *mini);
int			pipex(int argc, char **argv, char **envp, t_minishell *mini);
char		**create_pipex_commands(char **cmd, int cmd_num);
int			open_file(t_minishell *mini, char **argv, int **pipe_fd);
char		*get_filename(char *cmd);
char		*cleanup_input(char *cmd);
char		*cleanup_output(char *cmd);
char		*get_filename_out(char *cmd);
int			check_out_type(char *cmd);
int			check_in_type(char *cmd);
void		create_dumby_files(char *cmd, int **pipe_fd, t_minishell *mini);
int			create_file_dumb(char *cmd_name, char *cmd, int i);
void		create_dumbf_in(int i, char **argv, int **pipe_fd,
				t_minishell *mini);
void		create_dumbf_out(char **argv, int **pipe_fd, t_minishell *mini);
void		free_mini(t_minishell *mini);
void		free_error_fd(int **pipe_fd, t_minishell *mini);
void		free_error_dup(int **pipe_fd, t_minishell *mini, int fd);
char		*get_filename_pos(char *cmd, int i);
int			here_doc(char *cmd, t_minishell *mini, int **pipe_fd);
char		**here_maker(char *cmd);
int			here_doc_extra(char *cmd, int fd[2], t_minishell *mini,
				int **pipe_fd);
pid_t		here_doc_f(int fd[2], t_minishell *mini, int **pipe_fd);
int			check_here_doc(char **cmd, int j);
char		*input_code(char *file, char *argv, int **pipe_fd,
				t_minishell *mini);
void		single_command(char *argv, char **envp, t_minishell *mini);
char		*input_code_s(char *file, char *argv, int **pipe_fd,
				t_minishell *mini);
char		*create_dumbf_outs(char *argv, t_minishell *mini);
int			check_cmd(char *cmd);
int			check_cmd2(char *cmd);
void		excuate(char **command, char *command1, char **env);
void		excuate_s(char *command1, char **env);
// env
void		env_copy(char **env, t_minishell *mini);
void		print_env(char **env);
char		*env_key(char *cmd);
void		add_env(char **env, char *path);
#endif