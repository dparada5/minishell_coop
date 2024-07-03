/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:47:06 by dparada           #+#    #+#             */
/*   Updated: 2024/06/28 11:14:39 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

int	state_word(t_state *state, char *line)
{
	int	i;

	i = 0;
	state->type = S_W;
	while (line[i] != ' ' && line[i] != '\"' && line[i] != '\'' && line[i])
		i++;
	if (line[i] == ' ')
		state->type = S_S;
	return (i);
}

int	simple_quote(t_state *state, char *line, t_minishell *minishell)
{
	int	i;

	i = 1;
	state->type = S_QS;
	while (line[i] != '\'' && line[i])
		i++;
	if (line[i] == '\'')
	{
		state->type = S_W;
		return (i + 1);
	}
	else if (line[i] == '\0' && minishell->flag != 1)
	{
		msj_error(ERROR_SQ, minishell, 2);
		return (i);
	}
	return (0);
}

int	doble_quote(t_state *state, char *line, t_minishell *minishell)
{
	int	i;

	i = 1;
	state->type = S_DQ;
	while (line[i] != '\"' && line[i])
		i++;
	if (line[i] == '\"')
	{
		state->type = S_W;
		return (i + 1);
	}
	else if (line[i] == '\0' && minishell->flag != 1)
	{
		msj_error(ERROR_DQ, minishell, 2);
		return (i);
	}
	return (0);
}

void	states(char *line, t_minishell *minishell)
{
	t_state	*state;
	int		i;

	i = 0;
	state = malloc (sizeof(t_state));
	if (!state)
		return ;
	state->type = S_S;
	while (line[i])
	{
		if (line[i] == '\\' && (line[i + 1] == '\'' || line[i + 1] == '\"'))
			i += 2;
		else if (line[i] == '\'')
			i += simple_quote(state, &line[i], minishell);
		else if (line[i] == '\"')
			i += doble_quote(state, &line[i], minishell);
		else if (!ft_strchr("|<> ", line[i]))
			i += state_word(state, &line[i]);
		else
			i++;
	}
	free(state);
	state = NULL;
}
