/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:03:46 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/03/28 12:38:19 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_var = 99;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		if (waitpid(-1, NULL, WNOHANG) != -1)
			return ;
		rl_redisplay();
		return ;
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
}

void	child_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		g_signal_var = 130;
		return ;
	}
	else if (sig == SIGQUIT)
	{
		g_signal_var = 131;
		printf("Quit: 3\n");
		return ;
	}
}

void	heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		ft_putstr_fd("\n", 1);
		g_signal_var = 1;
	}
}

void	signal_case(int sig)
{
	if (g_signal_var == 3)
		child_signal(sig);
	else if (g_signal_var == 2)
		heredoc_signal(sig);
	else
		parent_signal(sig);
}

void	set_signals(t_minishell *mini)
{
	signal(SIGINT, signal_case);
	signal(SIGQUIT, signal_case);
	if (g_signal_var != 1)
		mini->exit_status = g_signal_var;
	g_signal_var = 1;
}
