/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:49:38 by dparada           #+#    #+#             */
/*   Updated: 2024/06/28 11:14:18 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

int	tokens(char *line, t_token **token, int *i, t_minishell *minishell)
{
	int	flag;

	flag = 0;
	if (line[*i] == '|')
	{
		flag = create_token(token, T_P, ft_strdup("|"), 0);
		(*i)++;
	}
	else if (line[*i] == '\'' || line[*i] == '\"')
		flag = quotes(token, line, line[*i], i);
	else if (line[*i] == '>')
		flag = greater_token(line, token, i, 0);
	else if (line[*i] == '<')
		flag = less_token(line, token, i, 0);
	if (flag == 1)
		msj_error(MALLOC_FAILED, minishell, 0);
	return (*i);
}

int	create_token(t_token **token, t_token_num token_num, \
char *content, int flag)
{
	t_token	*aux;

	if (!*token)
	{
		*token = new_token(token_num, content, flag);
		if (!*token)
			return (1);
	}
	else
	{
		aux = new_token(token_num, content, flag);
		if (!aux)
			return (1);
		ft_lstadd_back_token(token, aux);
	}
	free(content);
	content = NULL;
	return (0);
}

t_token	*get_tokens(char *line, t_minishell *minishell)
{
	int		i;
	t_token	*token;

	i = 0;
	token = NULL;
	if (minishell->flag != 1)
	{
		while (line[i])
		{
			while (line[i] == ' ')
				i++;
			if (ft_strchr("|<>\"'", line[i]))
				tokens(line, &token, &i, minishell);
			else
			{
				if (words(line, &token, &i, 1) == 1)
					msj_error(MALLOC_FAILED, minishell, 0);
			}
		}
		token_next(token, minishell);
	}
	return (token);
}
