/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:13:37 by dparada           #+#    #+#             */
/*   Updated: 2024/06/28 11:14:13 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

static char	*pop(t_token *token, char *aux2)
{
	t_token	*aux;
	char	*string;

	string = ft_strjoin(aux2, token->next->content);
	aux = token->next;
	token->next = aux->next;
	aux->next = NULL;
	ft_lstclear_token(aux);
	return (string);
}

static char	*check_join(t_token *aux)
{
	char	*aux2;
	char	*buffer;

	buffer = ft_strdup(aux->content);
	while (is_join (aux->next) == 1)
	{
		aux2 = buffer;
		buffer = pop(aux, aux2);
		aux2 = NULL;
	}
	return (buffer);
}

char	**cmds(t_token *tokens, int len, t_minishell *minishell)
{
	t_token	*aux;
	int		i;
	char	**matrix;

	aux = tokens;
	i = 0;
	matrix = ft_calloc(sizeof(char *), (len + 1));
	if (!matrix && minishell->flag != 1)
		msj_error(MALLOC_FAILED, minishell, 0);
	while (aux && aux->token != T_P)
	{
		if (aux->token >= T_G && aux->token <= T_DL)
			aux = aux->next;
		else if (ft_strlen(aux->content) != 0)
		{
			matrix[i++] = check_join(aux);
		}
		aux = aux->next;
	}
	matrix[i] = NULL;
	return (matrix);
}

