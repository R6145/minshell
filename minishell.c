/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:13:25 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/02/05 17:44:51 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		j;
	char	**x;
	char	*inpt;
	pid_t	pd;

	i = 0;
	(void)argc;
	(void)argv;
	(void)envp;
	j = 0;
	while (j < 10)
	{
		i = 0;
		inpt = readline("Enter text: ");
		// inpt = "'xxx;' ; 'xx' ";
		pd = fork();
		if (pd == 0)
		{
			x = cut_commands(inpt);
			// excute_command(x[0],envp);
				printf("%d\n", amount_of_commands(inpt));
				while (x[i] != NULL)
				{
				printf("%s\n", x[i]);
				i++;
				}
			freeall(x, amount_of_commands(inpt));
		}
		wait(NULL);
		// printf("%d",x);
		// printf("\n");
		// free(x);
		j++;
	}
	return (0);
}
