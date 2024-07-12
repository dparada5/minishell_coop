/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:10:36 by dparada           #+#    #+#             */
/*   Updated: 2024/07/12 13:40:46 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

void	ft_exit(int error_code, t_minishell *minishell, t_cmds *cmd)
{
	if (cmd->cmds_flags[1])
	{
		if (ft_is_num(cmd->cmds_flags[1]))
		{
			error_code = ft_atoi(cmd->cmds_flags[1]);
			ft_free_minishell(minishell, 1);
			exit (error_code % 256);
		}
		else
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: ", 1);
			ft_putstr_fd(cmd->cmds_flags[1], 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			ft_free_minishell(minishell, 1);
			exit(2);
		}
	}
	else
	{
		ft_free_minishell(minishell, 1);
		ft_putstr_fd("exit\n", 1);
		exit(error_code % 256);
	}
}
