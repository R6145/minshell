/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:38:24 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/03/25 17:46:15 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_copy(char **env, t_minishell *mini)
{
	int		i;
	char	**env_c;

	i = amount_of_arg(env) - 1;
	env_c = (char **)malloc(sizeof(char *) * (i + 1000));
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

char	*env_key(char *cmd)
{
	int		i;
	char	*file_name;

	i = 0;
	file_name = malloc(sizeof(char) * (ft_strlen(cmd) + 5));
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '=')
		{
			file_name[i] = '\0';
			return (file_name);
		}
		file_name[i] = cmd[i];
		i++;
	}
	file_name[i] = '\0';
	return (file_name);
}

void	print_env_expo(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("declare -x ");
		printf("%s\n", env[i]);
		i++;
	}
}

char	*bulid_env(char *key_env, char *path)
{
	int	i;
	int	j;

	i = 0;
	while (path[i] != '=' && path[i] != '\0')
		i++;
	if (path[i] == '\0' || path[i] == ' ')
	{
		j = ft_strlen(key_env);
		key_env[j++] = '=';
		key_env[j] = '\0';
		return (key_env);
	}
	free(key_env);
	return (ft_strdup(path));
}

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
