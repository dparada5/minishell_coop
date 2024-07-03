/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:01:06 by dparada           #+#    #+#             */
/*   Updated: 2023/12/21 16:13:01 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_new(char *ptr)
{
	int		i;
	int		n;
	int		len;
	char	*s;

	i = 0;
	len = ft_strlen(ptr);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	n = len - 1;
	while (len > 1)
	{
		s[i] = ptr[n];
		i++;
		n--;
	}
	s[i] = '\0';
	free(ptr);
	return (s);
}

char	*ft_convert_he(unsigned long nb, char *base)
{
	int				i;
	int				resto;
	unsigned long	nn;
	char			*ptr;
	char			*s;

	i = 0;
	nn = nb;
	i = ft_strdiv(nb);
	ptr = malloc(i + 1);
	i = 0;
	if (nn < 16 && nn >= 0)
		ptr[i++] = base[nn];
	else
	{
		while (nn != 0)
		{
			resto = nn % 16;
			ptr[i++] = base[resto];
			nn /= 16;
		}
	}
	ptr[i] = '\0';
	s = ft_new(ptr);
	return (s);
}

int	ft_hexa(unsigned long nb, char word)
{
	char	*low;
	char	*upper;
	char	*total;
	int		i;

	upper = "0123456789ABCDEF";
	low = "0123456789abcdef";
	i = 0;
	if (nb < 0)
		nb *= -1;
	if (word == 'x')
		total = ft_convert_he(nb, low);
	else
		total = ft_convert_he(nb, upper);
	i = ft_putstr(total);
	free(total);
	return (i);
}
