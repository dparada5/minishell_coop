/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:50:56 by dparada           #+#    #+#             */
/*   Updated: 2023/12/07 14:46:48 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_gnl(size_t count, size_t size)
{
	void	*punt;
	int		i;
	int		n;

	i = 0;
	n = (count * size);
	punt = malloc(n);
	if (punt == NULL || punt < 0)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)punt)[i] = 0;
		i++;
	}
	return (punt);
}

char	*ft_strjoin_gnl(char *buffer, char *line, int readline)
{
	char	*ptr;
	int		i;
	int		j;

	if (!buffer)
		buffer = ft_calloc_gnl(1, 1);
	ptr = malloc(ft_strlen_gnl(buffer) + readline + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (buffer[j])
		ptr[i++] = buffer[j++];
	j = 0;
	while (j < readline)
		ptr[i++] = line[j++];
	ptr[i] = '\0';
	free(buffer);
	return (ptr);
}

int	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0' && s[i] == '\0')
		return ((char *)&s[i]);
	return (0);
}
