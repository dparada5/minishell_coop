/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:47:32 by dparada           #+#    #+#             */
/*   Updated: 2023/12/07 14:46:28 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_readfd(int fd, char *buffer)
{
	int		readline;
	char	*line;
	char	*auxiliar;

	line = ft_calloc_gnl((BUFFER_SIZE + 1), sizeof(char));
	if (!line)
		return (NULL);
	readline = 1;
	while (!ft_strchr_gnl(line, '\n') && readline > 0)
	{
		readline = read(fd, line, BUFFER_SIZE);
		if (readline == -1)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		auxiliar = buffer;
		buffer = ft_strjoin_gnl(auxiliar, line, readline);
	}
	free(line);
	if (ft_strlen_gnl(buffer) == 0)
		return (free(buffer), NULL);
	return (buffer);
}

char	*ft_get_the_line(char *buffer)
{
	int		j;
	int		i;
	char	*line;

	j = 0;
	while (buffer[j] != '\n' && buffer[j] != '\0')
		j++;
	line = ft_calloc_gnl((j + 1 + (buffer[j] == '\n')), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_clean(char *buffer)
{
	int		j;
	int		i;
	char	*aux;

	j = 0;
	while (buffer[j] != '\0' && buffer[j] != '\n')
		j++;
	if (ft_strlen_gnl(buffer) - j <= 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	aux = ft_calloc_gnl(ft_strlen_gnl(buffer) - j + 1, sizeof(char));
	if (!aux)
		return (NULL);
	j++;
	i = 0;
	while (buffer[j] != '\0')
		aux[i++] = buffer[j++];
	free(buffer);
	buffer = NULL;
	return (aux);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read (fd, 0, 0) < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_readfd(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_the_line(buffer);
	buffer = ft_clean(buffer);
	return (line);
}
