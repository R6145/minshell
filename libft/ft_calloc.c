/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:54:33 by fmaqdasi          #+#    #+#             */
/*   Updated: 2023/07/19 14:23:48 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*st;

	if (size != 0 && (count > UINT32_MAX / size))
		return (NULL);
	st = malloc(count * size);
	if (!st)
		return (NULL);
	ft_bzero(st, count * size);
	return (st);
}
