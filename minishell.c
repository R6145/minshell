/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:13:25 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/02/07 22:59:43 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int			j;
	char		**x;
	char		**y;
	char		*inpt;
	pid_t		pd;
	t_minishell	mini;

	// int			i;
	// i = 0;
	(void)argc;
	(void)argv;
	(void)envp;
	j = 0;
	while (j < 10)
	{
		// i = 0;
		inpt = readline("Enter text: ");
		// inpt = "'xxx;' ; 'xx' ";
		pd = fork();
		if (pd == 0)
		{
			// (null) i;
			x = cut_commands(inpt);
			// excute_command(x[0],envp);
			mini.number_of_commands = (amount_of_commands(inpt) + 1) / 2;
			y = create_spilt_commands(x, mini.number_of_commands);
			// printf("%d\n", mini.number_of_commands);
			// while (y[i] != NULL)
			// {
			// 	printf("%s\n", y[i]);
			// 	i++;
			// }
			freeall(x, amount_of_commands(inpt));
			pipex(mini.number_of_commands + 3, y, envp);
			// freeall(y, mini.number_of_commands + 3);
		}
		wait(NULL);
		// printf("%d",x);
		// printf("\n");
		// free(x);
		j++;
	}
	return (0);
}
