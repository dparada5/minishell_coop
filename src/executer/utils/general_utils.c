/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:11:10 by dparada           #+#    #+#             */
/*   Updated: 2024/07/11 14:11:11 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

void	ft_free_mat(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i])
		free (mat[i]);
	free (mat);
}

int	ft_is_num(char	*str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

int	ft_wait(void)
{
	int	status;
	int	out_status;

	out_status = 0;
	wait (&status);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		out_status = WEXITSTATUS(status);
	else if (WIFEXITED(status) && WIFSIGNALED(status) != 0)
		out_status = WTERMSIG(status);
	else
		out_status = 0;
	return (out_status);
}

void	ft_free_and_exit(t_minishell *ms, int exit_v, char *er_msg, int exit_b)
{
	ft_free_minishell(ms, exit_b);
	if (exit_v)
		msj_error(er_msg, ms, exit_v);
	if (exit_b)
		exit (exit_v);
}

int	ft_export_chars(char *str, t_minishell *mshll)
{
	int	i;

	(void)mshll;
	if (!ft_isdigit(str[0]))
		return (0);
	i = -1;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}
