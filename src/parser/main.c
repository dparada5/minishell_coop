/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:17:45 by dparada           #+#    #+#             */
/*   Updated: 2024/07/11 14:17:51 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	(void)argv;
	if (argc == 1)
	{
		g_value = 1;
		minishell = malloc(sizeof(t_minishell));
		if (!minishell)
			msj_error(MALLOC_FAILED, minishell, 0);
		init_ev_exp(minishell, env);
		minishell->tokens = NULL;
		minishell->cmds = NULL;
		init_signal();
		if (minishell->flag != 1)
		{
			minishell->line = readline("minishell$ ");
			init_minishell(minishell);
			if (!minishell->line)
				control_d(minishell);
		}
	}
}
