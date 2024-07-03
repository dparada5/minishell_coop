/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:56:13 by dparada           #+#    #+#             */
/*   Updated: 2024/02/02 15:53:54 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_fatoi(int i, int n, int t, const char *str)
{
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i + 1] >= '0' && str [i + 1] <= '9')
		{
			if (str[i] == '-')
				t = -1;
		}
		else
			return (0);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - 48);
		i++;
	}
	return (t * n);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	t;

	i = 0;
	n = 0;
	t = 1;
	return (ft_fatoi(i, n, t, str));
}
