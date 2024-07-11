/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:11:12 by dparada           #+#    #+#             */
/*   Updated: 2024/07/11 14:11:13 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

int	ft_pipes_count(t_minishell *mshll)
{
	t_token	*runner;
	int		pipes;

	runner = mshll->tokens;
	pipes = 0;
	while (runner)
	{
		if (runner->token == T_P)
			pipes++;
		runner = runner->next;
	}
	return (pipes);
}
