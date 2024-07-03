/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:37:24 by dparada           #+#    #+#             */
/*   Updated: 2024/02/19 14:57:17 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*aux;

	if (!f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		aux = ft_lstnew(NULL);
		if (!aux)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		aux->content = f(lst->content);
		ft_lstadd_back(&new, aux);
		lst = lst->next;
	}
	return (new);
}
