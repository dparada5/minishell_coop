/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:46:51 by dparada           #+#    #+#             */
/*   Updated: 2024/07/02 19:26:50 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

void	control_c(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
}

void	control_d(t_minishell *minishell)
{
	ft_free_minishell(minishell, 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}

void	init_signal(void)
{
	signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);

	//CONTROLD if readline == NULL que vaya a la funcion control d, que haga un exit y escriba exit y libere memori
}