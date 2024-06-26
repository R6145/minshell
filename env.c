/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:38:24 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/06/20 18:01:18 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_copy(char **env, t_minishell *mini)
{
	int		i;
	char	**env_c;

	i = amount_of_arg(env) - 1;
	env_c = (char **)malloc(sizeof(char *) * (i + 3000));
	if (env_c == NULL)
		exit(2);
	env_c[i + 1] = NULL;
	while (i >= 0)
	{
		env_c[i] = ft_strdup(env[i]);
		i--;
	}
	mini->envps = env_c;
	update_lvl_env(mini->envps);
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
	int	j;

	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		printf("declare -x ");
		while (env[i][j] != '\0')
		{
			printf("%c", env[i][j]);
			if (env[i][j] == '=')
			{
				j++;
				printf("\"");
				while (env[i][j] != '\0')
					printf("%c", env[i][j++]);
				printf("\"");
				break ;
			}
			j++;
		}
		printf("\n");
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
