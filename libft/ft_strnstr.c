/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:12:39 by fmaqdasi          #+#    #+#             */
/*   Updated: 2023/07/18 10:36:25 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *haystack, char const *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (n == 0 && haystack == NULL)
		return (NULL);
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[i] != 0 && i < n)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (needle[j] != 0) && n >= j + i)
		{
			if (needle[j + 1] == '\0')
			{
				if (n - 1 < i + j)
					return (NULL);
				return ((char *)haystack + (i));
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
