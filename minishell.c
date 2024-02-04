/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:13:25 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/02/04 22:54:57 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		j;
	char	**x;
	char	*inpt;

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
		x = cut_commands(inpt);
		printf("%d\n", amount_of_commands(inpt));
		while (x[i] != NULL)
		{
			printf("%s\n", x[i]);
			i++;
		}
		freeall(x, amount_of_commands(inpt));
		// printf("%d",x);
		// printf("\n");
		// free(x);
		j++;
	}
	return (0);
}
