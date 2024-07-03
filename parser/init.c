/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:40:10 by dparada           #+#    #+#             */
/*   Updated: 2024/07/02 19:17:59 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"
//912

void	init_ev_exp(t_minishell *minishell, char **env)
{
	if (env != NULL)
	{
		minishell->env = save_env(env, -1, minishell);
		minishell->exp = save_env(env, -1, minishell);	
	}
	else
	{
		minishell->env = NULL;
		minishell->exp = NULL;
	}
	minishell->val_error = 0;
}

void	check_line(t_minishell *minishell)
{
	states(minishell->line, minishell);
	minishell->tokens = get_tokens(minishell->line, minishell);
	// printf_tokens(minishell->tokens);
	check_expansion(minishell->tokens, minishell);
	token_actions(minishell);
	// printf_cmds(minishell->cmds);
}

void	init_minishell(t_minishell *minishell)
{
	minishell->line = readline("minishell$ ");
	if (!minishell->line)
		control_d(minishell);
	while (minishell->line)
	{
		minishell->tokens = NULL;
		minishell->cmds = NULL;
		if (!ft_strlen(minishell->line))
		{
			minishell->line = readline("minishell$ ");
			continue ;
		}
		add_history(minishell->line);
		check_line(minishell);
		if (minishell->flag != 1)
		{
			ft_executor(minishell);
			minishell->val_error = 0;
		}
		// ft_putnbr_fd(minishell->flag, 2);
		ft_free_minishell(minishell, 0);
		minishell->line = readline("minishell$ ");
		if (!minishell->line)
			control_d(minishell);
	}
	rl_clear_history();
}
