/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:12:56 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/06/17 20:08:18 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_signal_var;

typedef struct s_list2
{
	char	**commands;
	char	**envps;
	int		number_of_commands;
	int		temp[3];
	char	*tempc;
	int		exit_status;
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
char		*cleanup_quotes(char *cmd);
char		*tab_to_space(char *cmd);
// freeing functions
void		freeall(char **st, int j);
void		free_pipe(int **fd);
void		free_split(char **var);
// excucation
char		*find_path(char **envp);
char		*create_command(char *command, char *path);
char		*create_command_extra(char *command, char *args);
int			excute_command(char **argv, t_minishell *mini, int x);
int			excute_command_d(char *cmd, t_minishell *mini);
pid_t		forking(int **fd, int argc);
int			**fd_create(int argc);
void		piping(int **x, int argc);
void		close_pipe(int **fd, int argc);
void		child(char **argv, int **pipe_fd, t_minishell *mini);
void		middle_child(char **argv, int **pipe_fd, t_minishell *mini);
void		middle(char **argv, int **pipe_fd, t_minishell *mini);
void		parent(char **argv, int **pipe_fd, t_minishell *mini);
int			pipex(int argc, char **argv, t_minishell *mini);
char		**create_pipex_commands(char **cmd, int cmd_num);
int			open_file(t_minishell *mini, char **argv, int **pipe_fd);
int			here_docking(char *file, char **argv, t_minishell *mini,
				int **pipe_fd);
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
void		single_command(char *argv, t_minishell *mini);
char		*input_code_s(char *file, char *argv, int **pipe_fd,
				t_minishell *mini);
char		*create_dumbf_outs(char *argv, t_minishell *mini);
int			check_cmd(char *cmd);
int			check_cmd2(char *cmd);
int			excuate(char **command, char *command1, t_minishell *mini);
int			excuate_s(char *command1, char **env);
void		excute_code(char **argv, int **pipe_fd, t_minishell *mini, int x);
char		*rp_cmd(char *cmd, char *key, char *des, int j);
char		*rp_cmd_emp(char *cmd, char *key, int j);
char		*enved_cmd(char *cmd, char *cmd1, int j, t_minishell *mini);
char		*env_handling(char *cmd, t_minishell *mini);
int			between_sq(char *cmd, int j);
int			between(char *cmd, int j);
int			between_extra(char *cmd, int i0, int i1, int i2);
int			between2(char *cmd, int j);
int			between_state(int state);
// buldiin
void		exiting(char *command1, t_minishell *mini);
void		get_pwd(void);
void		update_opwd(char **env, int j);
void		update_pwd(char **env);
int			cd(char **env, char *path);
void		echo(char **cmd);
// env
void		env_copy(char **env, t_minishell *mini);
void		print_env(char **env);
char		*env_key(char *cmd);
void		add_env(char **env, char *path);
void		env_add_emv(char **env, char *env_1);
void		add_remove_all_env(char **env, char **arg, int flag);
char		*bulid_env(char *key_env, char *path);
void		print_env_expo(char **env);
void		remove_env(char **env, char *path);
void		update_lvl_env(char **env);
// error
int			check_dq(char *cmd);
int			check_sq(char *cmd);
int			redir_check(char *cmd);
int			redir_check2(char *cmd);
int			redir_check3(char *cmd);
int			error_checker(char *cmdl);
int			pipe_check(char *cmd);
// signal
void		signal_handler_parent(int signum);
void		close_g_signal_var(void);
#endif