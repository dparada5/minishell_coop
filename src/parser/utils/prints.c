/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:09:16 by dparada           #+#    #+#             */
/*   Updated: 2024/06/28 11:14:37 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

void	printf_cmds(t_cmds *cmds)
{
	int		i;
	t_cmds	*aux;

	aux = cmds;
	while (aux)
	{
		i = 0;
		printf("Command: %s %d %d\n", aux->cmds, aux->fd_in, aux->fd_out);
		while (aux->cmds_flags[i])
		{
			printf("\tFlags: %s\n", aux->cmds_flags[i]);
			i++;
		}
		aux = aux->next;
	}
	printf("------------------------------------------\n");
}

void	printf_tokens(t_token *token)
{
	t_token	*aux;

	aux = token;
	while (aux)
	{
		if (aux->token == T_W)
			printf("Token:	W\t");
		else if (aux->token == T_DQ)
			printf("Token: DQ\t");
		else if (aux->token == T_SQ)
			printf("Token: SQ\t");
		else if (aux->token == T_P)
			printf("Token:	P\t");
		else if (aux->token == T_G)
			printf("Token:	G\t");
		else if (aux->token == T_L)
			printf("Token:	L\t");
		else if (aux->token == T_DG)
			printf("Token:  DG\t");
		else if (aux->token == T_DL)
			printf("Token:	DL\t");
		printf("Flag: %d\tContent: %s\n", aux->flag, aux->content);
		aux = aux->next;
	}
	printf("------------------------------------------\n");
}

void	print_env(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		printf("%sKey:%s %s\t%sContent:%s%s\n", \
		RED, RST, aux->key, RED, RST, aux->content);
		aux = aux->next;
	}
}

void	print_state(t_state *state)
{
	if (state->type == S_S)
		printf("STATE == START\n");
	else if (state->type == S_W)
		printf("STATE == WORD\n");
	else if (state->type == S_QS)
		printf("STATE == SIMPLE QUOT\n");
	else if (state->type == S_DQ)
		printf("STATE == DOBLE QUOTES\n");
	else if (state->type == S_D)
		printf("STATE == DOLAR\n");
	else if (state->type == S_CD)
		printf("STATE == COMILLA CON DOLAR\n");
	else if (state->type == S_SU)
		printf("STATE == SUMILERO (?\n");
}
