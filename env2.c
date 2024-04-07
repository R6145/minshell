/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:38:24 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/04/07 19:59:43 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_add_emv(char **env, char *env_1)
{
	int	i;

	i = amount_of_arg(env);
	env[i++] = env_1;
	env[i] = NULL;
}

void	add_env(char **env, char *path)
{
	int		i;
	char	*key;
	char	*key_env;

	i = 0;
	if (path == NULL)
		return (print_env_expo(env));
	key = env_key(path);
	while (env[i] != NULL)
	{
		key_env = env_key(env[i]);
		if (ft_strncmp(key, key_env, ft_strlen(key_env) + ft_strlen(key)) == 0)
		{
			free(env[i]);
			env[i] = bulid_env(key_env, path);
			free(key);
			return ;
		}
		free(key_env);
		i++;
	}
	env_add_emv(env, bulid_env(key, path));
}

void	remove_env(char **env, char *path)
{
	int		i;
	char	*key_env;

	i = 0;
	if (path == NULL)
		return ;
	while (env[i] != NULL)
	{
		key_env = env_key(env[i]);
		if (ft_strncmp(path, key_env, ft_strlen(key_env)
				+ ft_strlen(path)) == 0)
		{
			free(env[i]);
			free(key_env);
			while (env[i] != NULL)
			{
				env[i] = env[i + 1];
				i++;
			}
			return ;
		}
		free(key_env);
		i++;
	}
}
