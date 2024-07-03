/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:00:03 by dparada           #+#    #+#             */
/*   Updated: 2023/12/07 15:21:41 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*aux;

	if (!lst)
		return (0);
	i = 1;
	aux = lst;
	while (aux->next)
	{
		aux = aux->next;
		i++;
	}
	return (i);
}
