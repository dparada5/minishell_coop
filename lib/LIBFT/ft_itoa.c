/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:48:51 by dparada           #+#    #+#             */
/*   Updated: 2024/02/20 13:45:38 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digit(long n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 9)
	{
		n = (n / 10);
		i++;
	}
	return (i);
}

char	*ft_convert(long n, char *ptr, size_t i)
{
	if (n < 0)
	{
		ptr[0] = '-';
		n *= -1;
	}
	if (n == 0)
		ptr[0] = '0';
	while (n > 9)
	{
		ptr[--i] = (n % 10) + '0';
		n /= 10;
	}
	if (n > 0)
		ptr[--i] = n + '0';
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	size_t	i;
	long	nl;

	nl = (long)n;
	i = ft_digit(nl);
	ptr = malloc ((i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[i] = '\0';
	ptr = ft_convert(nl, ptr, i);
	return (ptr);
}
