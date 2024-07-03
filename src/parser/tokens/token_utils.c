/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:00:36 by dparada           #+#    #+#             */
/*   Updated: 2024/06/28 11:14:26 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

t_token	*new_token(t_token_num token_num, char *content, int flag)
{
	t_token	*token;

	token = malloc (sizeof(t_token));
	if (!token)
		return (NULL);
	token->token = token_num;
	token->content = ft_strdup(content);
	if (!token->content)
		return (NULL);
	token->flag = flag;
	token->next = NULL;
	return (token);
}

t_token	**ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*aux;

	aux = *lst;
	if (!(*lst))
		(*lst) = new;
	else if (*lst)
	{
		while ((*lst)->next)
			(*lst) = (*lst)->next;
		(*lst)->next = new;
		(*lst) = aux;
	}
	return (lst);
}

void	token_next_part_two(t_token *token, t_minishell *minishell)
{
	t_token	*aux;

	aux = token;
	if (aux->token >= T_G && aux->token <= T_DL && minishell->flag != 1)
	{
		if (aux->next != NULL && aux->next->token != T_W \
		&& aux->next->token != T_DQ && aux->next->token != T_SQ \
		&& minishell->flag != 1)
			msj_error(ERROR_UT, minishell, 2);
	}
	else if (aux->token == T_P && aux->next && aux->next->token == T_P \
	&& minishell->flag != 1)
		msj_error(ERROR_UT, minishell, 2);
}

void	token_next(t_token *token, t_minishell *minishell)
{
	t_token	*aux;
	int		flag;

	flag = 0;
	aux = token;
	while (aux)
	{
		if (((aux->next == NULL && aux->token == T_P) || aux->flag == 2) \
		&& minishell->flag != 1)
			msj_error(ERROR_EOF, minishell, 130);
		if ((aux->next == NULL && aux->token != T_W && aux->token != T_DQ \
		&& aux->token != T_SQ) && minishell->flag != 1)
			msj_error(ERROR_UT, minishell, 2);
		else if (aux->token == T_P && flag == 0 && minishell->flag != 1)
			msj_error(ERROR_UPIPE, minishell, 2);
		else if (minishell->flag != 1)
			token_next_part_two(aux, minishell);
		aux = aux->next;
		flag = 1;
	}
}
