/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:38:24 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/06/17 17:38:33 by fmaqdasi         ###   ########.fr       */
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
	if (i <= 2950)
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

void	update_lvl_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			temp = env[i] + 6;
			j = ft_atoi(temp);
			j++;
			free(env[i]);
			temp = ft_itoa(j);
			env[i] = ft_strjoin("SHLVL=", temp);
			free(temp);
			return ;
		}
		i++;
	}
}

void	add_remove_all_env(char **env, char **arg, int flag)
{
	int	i;

	i = 1;
	if (flag == 0)
	{
		if (arg[1] == NULL)
			return (print_env_expo(env));
		while (arg[i] != NULL)
		{
			add_env(env, arg[i]);
			i++;
		}
	}
	else if (flag == 1)
	{
		while (arg[i] != NULL)
		{
			remove_env(env, arg[i]);
			i++;
		}
	}
}
