/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:48:52 by fmaqdasi          #+#    #+#             */
/*   Updated: 2023/07/18 10:58:05 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*st;
	int		i;

	i = 0;
	st = (char *)malloc(ft_strlen(src)+1);
	if (!st)
		return (NULL);
	while (src[i])
	{
		st[i] = (char)src[i];
		i++;
	}
	st[i] = '\0';
	return ((char *)st);
}
