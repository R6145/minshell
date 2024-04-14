/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:13:25 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/04/14 16:32:11 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal_var = 0;

static void	minishell_exc(t_minishell *mini, char *inpt)
{
	char	**x;
	int		pd;
	int		status;

	g_signal_var = 2;
	pd = fork();
	if (pd == 0)
	{
		x = cut_commands(inpt);
		mini->number_of_commands = amount_of_commands(inpt);
		if (mini->number_of_commands == 1)
		{
			single_command(inpt, mini);
		}
		else
		{
			mini->commands = create_pipex_commands(x, mini->number_of_commands);
			freeall(x, mini->number_of_commands);
			free(inpt);
			pipex(mini->number_of_commands + 3, mini->commands, mini);
		}
	}
	waitpid(pd, &status, 0);
	mini->exit_status = WEXITSTATUS(status);
}

static void	minishell_choice(t_minishell *mini, char *inpt)
{
	if (inpt == NULL)
		return (ft_putstr_fd("\n", 2), free_mini(mini), exit(0));
	if (inpt != NULL && inpt[0] != '\0')
	{
		add_history(inpt);
		mini->number_of_commands = amount_of_commands(inpt);
		if (error_checker(inpt))
		{
			ft_putstr_fd("\n", 2);
			mini->exit_status = 2;
		}
		else if (mini->number_of_commands == 1 && check_cmd2(inpt) == 1)
		{
			exiting(inpt, mini);
			mini->exit_status = excuate_s(inpt, mini->envps);
		}
		else
			minishell_exc(mini, inpt);
	}
	if (inpt != NULL)
		free(inpt);
}

int	main(int argc, char **argv, char **envp)
{
	char		*inpt;
	t_minishell	mini;

	(void)argc;
	(void)argv;
	inti(&mini);
	env_copy(envp, &mini);
	signal(SIGINT, signal_handler_parent);
	signal(SIGQUIT, signal_handler_parent);
	while (g_signal_var != 4)
	{
		g_signal_var = -1;
		inpt = readline("minishell: ");
		tab_to_space(inpt);
		minishell_choice(&mini, inpt);
	}
	free_mini(&mini);
	return (0);
}
