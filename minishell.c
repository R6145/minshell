/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:13:25 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/06/24 16:42:11 by fmaqdasi         ###   ########.fr       */
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
			freeall(x, mini->number_of_commands);
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
			if (error_checker(inpt) == 4 || error_checker(inpt) == 5)
				mini->exit_status = 258;
			else
				mini->exit_status = 2;
		}
		else if (mini->number_of_commands == 1 && check_cmd2(inpt) == 1)
		{
			exiting(inpt, mini);
			mini->exit_status = excuate_s(inpt, mini->envps, mini);
			inpt = NULL;
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
		if (inpt == NULL && g_signal_var == -1)
			return (printf("exit\n"), exiting(ft_strdup("exit"), &mini),
				free_mini(&mini), 0);
		if (inpt != NULL)
		{
			tab_to_space(inpt);
			minishell_choice(&mini, inpt);
		}
	}
	free_mini(&mini);
	return (0);
}
