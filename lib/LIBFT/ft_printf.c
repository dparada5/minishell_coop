/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:43:28 by dparada           #+#    #+#             */
/*   Updated: 2023/12/21 16:13:53 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check(char const *str, va_list parametros, int total)
{
	int		i;
	char	word;
	char	*ptr;

	i = 0;
	word = str[i];
	if (str[i] == '%')
		total += ft_putchar('%');
	else if (str[i] == 'c')
		total += ft_putchar(va_arg(parametros, int));
	else if (str[i] == 's')
		total += ft_putstr(va_arg(parametros, char *));
	else if (str[i] == 'd' || str[i] == 'i')
	{
		ptr = ft_itoap(va_arg(parametros, int));
		total += ft_putstr(ptr);
		free(ptr);
	}
	total += ft_check_hexa(str, parametros);
	return (total);
}

int	ft_check_hexa(char const *str, va_list parametros)
{
	char	*ptr;
	char	word;
	int		total;
	int		i;

	i = 0;
	total = 0;
	word = str[i];
	if (str[i] == 'x' || str[i] == 'X')
		total += ft_hexa(va_arg(parametros, unsigned int), word);
	else if (str[i] == 'p')
		total += ft_punt(va_arg(parametros, void *));
	else if (str[i] == 'u')
	{
		ptr = ft_itoa_u(va_arg(parametros, unsigned int));
		total += ft_putstr(ptr);
		free(ptr);
	}
	return (total);
}

int	ft_printf(char const *str, ...)
{
	int		i;
	int		cont;
	va_list	parametros;

	i = 0;
	cont = 0;
	va_start(parametros, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			cont = ft_check(&str[i], parametros, cont);
		}
		else
			cont += ft_putchar(str[i]);
		i++;
	}
	va_end(parametros);
	return (cont);
}
