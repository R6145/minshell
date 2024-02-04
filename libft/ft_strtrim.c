/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 09:56:00 by fmaqdasi          #+#    #+#             */
/*   Updated: 2023/07/18 10:41:14 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char s, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*st;
	size_t	i;
	size_t	sta;
	size_t	end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	sta = 0;
	end = ft_strlen(s1);
	i = 0;
	while (s1[sta] != '\0' && check(s1[sta], set))
		sta++;
	while (end > sta && check(s1[end - 1], set))
		end--;
	st = (char *)malloc(end - sta + 1);
	if (!st)
		return (NULL);
	while (sta < end)
	{
		st[i] = s1[sta];
		sta++;
		i++;
	}
	st[i] = '\0';
	return (st);
}
