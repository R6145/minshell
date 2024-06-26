/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:03:46 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/06/24 16:09:11 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_g_signal_var(void)
{
	close(g_signal_var);
	g_signal_var = 0;
}

static void	heredoc_prompt(void)
{
	rl_on_new_line();
	ft_putstr_fd(" \b\b\n", 2);
	g_signal_var = 1;
	close(g_signal_var);
	close(0);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_var = 130;
}

static void	command_prompt(void)
{
	g_signal_var = -2;
}

static void	minishell_prompt(void)
{
	rl_on_new_line();
	ft_putstr_fd(" \b\b\n", 2);
	g_signal_var = -1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		if (g_signal_var == -1 || g_signal_var == 1)
			minishell_prompt();
		else if (g_signal_var == 2)
			command_prompt();
		else
			heredoc_prompt();
	}
	if (signum == SIGQUIT && (g_signal_var == -1 || g_signal_var == 1))
	{
		g_signal_var = -1;
	}
	if (signum == SIGQUIT && g_signal_var == -2)
	{
		ft_putstr_fd("Quit:", 2);
		ft_putstr_fd("\n", 2);
		g_signal_var = -4;
	}
}
