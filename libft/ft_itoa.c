/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:54:39 by fmaqdasi          #+#    #+#             */
/*   Updated: 2023/07/16 13:20:11 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(int n)
{
	int	i;

	i = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*st;
	int			a;
	long int	x;

	x = n;
	a = count(n);
	if (0 > x)
	{
		x = x * -1;
		a++;
	}
	st = (char *)malloc(a + 1);
	if (!st)
		return (NULL);
	st[a] = '\0';
	while (a--)
	{
		st[a] = (x % 10) + '0';
		x = x / 10;
	}
	if (n < 0)
		st[0] = '-';
	return (st);
}
