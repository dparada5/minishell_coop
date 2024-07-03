/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:46:28 by dparada           #+#    #+#             */
/*   Updated: 2024/06/28 11:14:05 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

static char	**create_mat(t_minishell *minishell)
{
	char	**split;

	split = ft_calloc(sizeof(char *), 2);
	split[0] = ft_strdup("");
	if (!split || !split[0])
		msj_error(MALLOC_FAILED, minishell, 0);
	split[1] = NULL;
	return (split);
}

t_token	*command_words(t_token *aux, int i, \
t_minishell *minishell, t_token *token)
{
	char	**split;
	t_cmds	*aux_cmd;
	t_token	*save;

	save = aux;
	while (aux && aux->token != T_P)
	{
		if (aux->token >= T_G && aux->token <= T_DL)
			aux = aux->next;
		if (is_join(aux->next) == 0)
			i++;
		aux = aux->next;
	}
	if (i != 0)
		split = cmds(save, i, minishell);
	else
		split = create_mat(minishell);
	if (minishell->cmds)
	{
		aux_cmd = new_cmd(i, split, token, minishell);
		ft_lstadd_back_cmd(&minishell->cmds, aux_cmd);
	}
	else
		minishell->cmds = new_cmd(i, split, token, minishell);
	return (aux);
}

t_token	*command_create(t_token *token, t_minishell *minishell)
{
	t_token	*aux;

	aux = token;
	while (aux && aux->token != T_P)
	{
		if (aux->token >= T_G && aux->token <= T_DL)
			aux = aux->next;
		else if (ft_strlen(aux->content) > 0)
			break ;
		aux = aux->next;
	}
	if (!aux || (aux && aux->token == T_P))
		aux = command_words(token, 0, minishell, token);
	else if (aux)
		aux = command_words(aux, 1, minishell, token);
	return (aux);
}

void	token_actions(t_minishell *minishell)
{
	t_token	*aux;
	int		i;

	i = 0;
	aux = minishell->tokens;
	if (minishell->flag != 1)
	{
		while (aux)
		{
			if (aux && aux->token == T_P)
				aux = aux->next;
			if (aux)
				aux = command_create(aux, minishell);
		}
	}
}
