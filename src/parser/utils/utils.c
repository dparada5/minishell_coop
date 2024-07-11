/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:17:12 by dparada           #+#    #+#             */
/*   Updated: 2024/07/11 14:17:15 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

void	msj_error(char *str, t_minishell *minishell, int val_error)
{
	if (errno)
		perror(str);
	else
	{
		if (str)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
		}
	}
	minishell->val_error = val_error;
	minishell->flag = 1;
}

int	is_join(t_token *tokens)
{
	if (tokens && (tokens->token == T_W \
	|| tokens->token == T_DQ || tokens->token == T_SQ))
	{
		if (tokens->content && tokens->flag == 1)
			return (1);
	}
	else
		return (2);
	return (0);
}
