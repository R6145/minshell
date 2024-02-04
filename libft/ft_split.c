/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:24:54 by fmaqdasi          #+#    #+#             */
/*   Updated: 2023/11/12 14:29:33 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s && *s != c)
	{
		count++;
		s++;
	}
	return (count);
}

static int	amountofwords(char const *s, char c)
{
	int	amount;
	int	is_word;

	amount = 0;
	is_word = 0;
	while (*s)
	{
		if (*s == c)
			is_word = 0;
		else if (!is_word)
		{
			is_word = 1;
			amount++;
		}
		s++;
	}
	return (amount);
}

static void	freeall(char **st, int j)
{
	while (j >= 0)
	{
		free(st[j]);
		j--;
	}
	free(st);
}

static int	asign(char **t, char const *s, char c, int a)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (j < a)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		t[j] = ft_substr(s, i, len(s + i, c));
		if (!t[j])
		{
			freeall(t, j - 1);
			return (-1);
		}
		i = i + len(s + i, c);
		j++;
	}
	t[j] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**t;
	int		a;

	if (!s)
		return (NULL);
	a = amountofwords(s, c);
	t = (char **)malloc(sizeof(char *) * (a + 1));
	if (!t)
		return (NULL);
	if (asign(t, s, c, a) == -1)
		return (NULL);
	return (t);
}
