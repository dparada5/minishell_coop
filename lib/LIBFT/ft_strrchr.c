/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:48:03 by dparada           #+#    #+#             */
/*   Updated: 2023/10/11 10:41:02 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*l;

	i = 0;
	l = 0;
	while (s[i])
	{
		if (s[i] == (char )c)
			l = &s[i];
		i++;
	}
	if ((char )c == '\0' && s[i] == '\0')
		return ((char *)&s[i]);
	return ((char *)l);
}
