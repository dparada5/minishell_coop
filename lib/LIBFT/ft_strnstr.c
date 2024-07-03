/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:26:22 by dparada           #+#    #+#             */
/*   Updated: 2023/10/11 10:40:50 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cmp(const char *s1, const char *s2, size_t i, size_t l)
{
	size_t	n;

	n = 0;
	while (s2[n])
	{
		if (i >= l || (s1[i] != s2[n]))
			return (0);
		i++;
		n++;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		if (needle[0] == haystack[i])
		{
			if (ft_cmp(haystack, needle, i, len) == 1)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
