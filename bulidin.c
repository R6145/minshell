/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulidin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:48:19 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/03/22 22:33:18 by fmaqdasi         ###   ########.fr       */
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

// void	cd(void)
// {
// 	char	x[1000];

// 	if (getcwd(x, 1000))
// 	{
// 		printf("%s\n", x);
// 	}
// 	return ;
// }
