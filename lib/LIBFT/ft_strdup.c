/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:52:06 by dparada           #+#    #+#             */
/*   Updated: 2024/06/26 13:34:41 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*punt;
	int		i;

	i = 0;
	punt = ((char *)malloc (sizeof(char) * ft_strlen(s1) + 1));
	if (punt == NULL || punt < 0)
		return (NULL);
	while (s1[i])
	{
		punt[i] = s1[i];
		i++;
	}
	punt[i] = '\0';
	return (punt);
}

// && s1[i] != ' '