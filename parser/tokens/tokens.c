/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:30:55 by dparada           #+#    #+#             */
/*   Updated: 2024/07/02 15:38:15 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

int	back_slash(char *line, t_token **token, int *i, int flag)
{
	int	start;
	int	error;

	start = *i;
	error = 0;
	if (*i > 0 && line[*i - 1] == ' ' && flag != 0)
		flag = 0;
	if (line[*i] == '\\' && line[*i + 1] == '\0')
	{
		error = create_token(token, T_W, ft_strdup(""), 2);
		(*i)++;
	}
	else if (line[*i] == '\\')
	{
		start = ++*i;
		if (line[*i] == '$' || line[*i] == '~')
			start--;
		error = create_token(token, T_W, ft_substr(line, start, ++*i - start), \
		flag);
	}
	return (error);
}

int	words(char *line, t_token **token, int *i, int flag)
{
	int	start;
	int	error;

	start = *i;
	error = 0;
	if (*i > 0 && line[*i - 1] == ' ' && flag != 0)
		flag = 0;
	if (line[*i] == '\\')
		error = back_slash(line, token, i, flag);
	else
	{
		while (!ft_strchr("| <>\"\'\\", line[*i]) && line[*i])
			(*i)++;
		error = create_token(token, T_W, ft_substr(line, start, *i - start), \
		flag);
	}
	return (error);
}

int	greater_token(char *line, t_token **token, int *i, int flag)
{
	int	error;

	error = 0;
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		error = create_token(token, T_DG, ft_strdup(">>"), flag);
		*i += 1;
	}
	else
		error = create_token(token, T_G, ft_strdup(">"), flag);
	*i += 1;
	return (error);
}

int	less_token(char *line, t_token **token, int *i, int flag)
{
	int	error;

	error = 0;
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		error = create_token(token, T_DL, ft_strdup("<<"), flag);
		*i += 1;
	}
	else
		error = create_token(token, T_L, ft_strdup("<"), flag);
	*i += 1;
	return (error);
}

int	quotes(t_token **tokens, char *line, char c, int *i)
{
	int	flag;
	int	start;
	int	error;

	error = 0;
	flag = 1;
	if (*i > 0 && line[*i - 1] == ' ' && flag != 0)
		flag = 0;
	start = ++(*i);
	while (line[*i] && line[*i] != c)
		(*i)++;
	if (c == '\"')
		error = create_token(tokens, T_DQ, ft_substr(line, start, *i - start), \
		flag);
	else if (c == '\'')
		error = create_token(tokens, T_SQ, ft_substr(line, start, *i - start), \
		flag);
	if (line[*i] == c)
		(*i)++;
	return (error);
}
