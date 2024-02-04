/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:07:52 by fmaqdasi          #+#    #+#             */
/*   Updated: 2023/07/18 10:38:44 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void const *s1, void const *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (n - i > 1 && *((unsigned char *)s1) == *((unsigned char *)s2))
	{
		s1 = (unsigned char *)s1 + 1;
		s2 = (unsigned char *)s2 + 1;
		i++;
	}
	return (*((unsigned char *)s1) - *((unsigned char *)s2));
}
