/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulidin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:48:19 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/03/24 19:28:17 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pwd(void)
{
	char	x[1000];

	if (getcwd(x, 1000))
	{
		printf("%s\n", x);
	}
	return ;
}

void	update_opwd(char **env, int j)
{
	int		i;
	char	*key_env;

	i = 0;
	while (env[i] != NULL)
	{
		key_env = env_key(env[i]);
		if (ft_strncmp("OLDPWD", key_env, 7) == 0)
		{
			free(env[i]);
			free(key_env);
			if (j == -1)
				env[i] = ft_strdup("OLDPWD=");
			else
				env[i] = ft_strjoin("OLDPWD=", env[j] + 4);
			return ;
		}
		free(key_env);
		i++;
	}
	if (j == -1)
		env_add_emv(env, ft_strdup("OLDPWD="));
	else
		env_add_emv(env, ft_strjoin("OLDPWD=", env[j] + 4));
}

void	update_pwd(char **env)
{
	int		i;
	char	*key_env;
	char	path[1000];

	i = 0;
	getcwd(path, 1000);
	while (env[i] != NULL)
	{
		key_env = env_key(env[i]);
		if (ft_strncmp("PWD", key_env, 4) == 0)
		{
			update_opwd(env, i);
			free(env[i]);
			free(key_env);
			env[i] = ft_strjoin("PWD=", path);
			return ;
		}
		free(key_env);
		i++;
	}
	env_add_emv(env, ft_strjoin("PWD=", path));
	update_opwd(env, -1);
}

int	cd(char **env, char *path)
{
	int	stat;

	stat = chdir(path);
	if (stat == -1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		return (1);
	}
	update_pwd(env);
	return (0);
}
