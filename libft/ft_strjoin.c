/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:42:41 by fmaqdasi          #+#    #+#             */
/*   Updated: 2023/07/19 12:55:53 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*st;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	st = (char *)malloc(j + ft_strlen(s2) + 1);
	if (!st)
		return (NULL);
	while (s1[i])
	{
		st[i] = s1[i];
		i++;
	}
	while (s2[i - j])
	{
		st[i] = s2[i - j];
		i++;
	}
	st[i] = '\0';
	return (st);
}
