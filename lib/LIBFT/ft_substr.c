/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:10:19 by dparada           #+#    #+#             */
/*   Updated: 2024/06/12 14:05:04 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	n;
	char	*ptr;

	i = start;
	n = 0;
	if (ft_strlen(s) == 0 || len < 0 || start < 0 || start > ft_strlen(s))
		return ((char *)ft_calloc(1, 1));
	while (s[i] && n < len)
	{
		i++;
		n++;
	}
	ptr = (char *)malloc((n + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[n] = '\0';
	return (ptr);
}
