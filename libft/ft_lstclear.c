/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 09:54:57 by fmaqdasi          #+#    #+#             */
/*   Updated: 2023/11/12 14:59:14 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*x;
	t_list	*xn;

	if (lst == NULL || del == NULL || *lst == NULL)
		return ;
	x = *lst;
	while (x != NULL)
	{
		xn = x->next;
		del(x->content);
		free(x);
		x = xn;
	}
	*lst = NULL;
}
