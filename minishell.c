/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:13:25 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/03/22 21:41:40 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pipex test

// int	error_handling(t_minishell *mini)
// {
// 	if (mini->number_of_commands % 2 = 0)

// 		return (1);
// }

int	main(int argc, char **argv, char **envp)
{
	int			j;
	char		**x;
	char		*inpt;
	pid_t		pd;
	t_minishell	mini;
	int			status;

	(void)argc;
	(void)argv;
	j = 0;
	inti(&mini);
	env_copy(envp, &mini);
	while (1 == 1)
	{
		inpt = readline("Enter text: ");
		if (inpt[0] != '\0')
		{
			add_history(inpt);
			mini.number_of_commands = amount_of_commands(inpt);
			// printf("%d\n", check_cmd2(inpt));
			if (mini.number_of_commands == 1 && check_cmd2(inpt) == 1)
			{
				exiting(inpt, &mini);
				excuate_s(inpt, mini.envps);
				pd = -1;
			}
			else
				pd = fork();
			if (pd == 0)
			{
				// printf("here\n");
				x = cut_commands(inpt);
				mini.number_of_commands = amount_of_commands(inpt);
				if (mini.number_of_commands == 1)
				{
					single_command(inpt, mini.envps, &mini);
				}
				else
				{
					mini.commands = create_pipex_commands(x,
							mini.number_of_commands);
					freeall(x, mini.number_of_commands);
					free(inpt);
					// printf("%d\n", mini.number_of_commands);
					pipex(mini.number_of_commands + 3, mini.commands,
						mini.envps, &mini);
				}
			}
			if (inpt != NULL)
				free(inpt);
			wait(&status);
			printf("%d\n", WEXITSTATUS(status));
		}
		j++;
	}
	free_mini(&mini);
	return (0);
}

// arg split test

// int	main(int argc, char **argv, char **envp)
// {
// 	int			j;
// 	char		**x;
// 	char		*inpt;
// 	int			i;
// 	t_minishell	mini;

// 	// pid_t		pd;
// 	// char		**y;
// 	i = 0;
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	j = 0;
// 	while (j < 10)
// 	{
// 		i = 0;
// 		inpt = readline("Enter text: ");
// 		add_history(inpt);
// 		inti(&mini);
// 		// inpt = "'xxx;' ; 'xx' ";
// 		// pd = fork();
// 		// if (pd == 0)
// 		// {
// 		// (null) i;
// 		x = cut_commands(inpt);
// 		// excute_command(x[0],envp);
// 		// mini.number_of_commands = (amount_of_commands(inpt) + 1) / 2;
// 		// y = create_pipex_commands(x, mini.number_of_commands);
// 		// printf("%d\n", mini.number_of_commands);
// 		check_for_ipop(&mini, x);
// 		while (x[i] != NULL)
// 		{
// 			printf("%s\n", x[i]);
// 			printf("%d\n", mini.input[i]);
// 			printf("%d\n", mini.output[i]);
// 			printf("%d\n", mini.inp_type[i]);
// 			printf("%d\n", mini.out_type[i]);
// 			printf("|||||||||\n");
// 			i++;
// 		}
// 		freeall(x, amount_of_commands(inpt));
// 		// pipex(mini.number_of_commands + 3, y, envp);
// 		// freeall(y, mini.number_of_commands + 3);
// 		// }
// 		// wait(NULL);
// 		// printf("%d",x);
// 		// printf("\n");
// 		// free(x);
// 		j++;
// 	}
// 	return (0);
// }

// single command

// int	main(int argc, char **argv, char **envp)
// {
// 	int			j;
// 	// char		**x;
// 	// char		**y;
// 	char		*inpt;
// 	pid_t		pd;
// 	// t_minishell	mini;

// 	(void)argc;
// 	(void)argv;
// 	j = 0;
// 	while (j < 10)
// 	{
// 		inpt = readline("Enter text: ");
// 		add_history(inpt);
// 		pd = fork();
// 		if (pd == 0)
// 		{
// 			excute_command_d(inpt, envp);
// 		}
// 		wait(NULL);
// 		j++;
// 	}
// 	return (0);
// }

// do error handling