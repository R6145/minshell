/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:38:24 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/03/20 15:32:38 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_copy(char **env, t_minishell *mini)
{
	int		i;
	char	**env_c;

	i = amount_of_arg(env) - 1;
	env_c = (char **)malloc(sizeof(char *) * (i + 2));
	if (env_c == NULL)
		exit(2);
	env_c[i + 1] = NULL;
	while (i >= 0)
	{
		env_c[i] = ft_strdup(env[i]);
		i--;
	}
	mini->envps = env_c;
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}
