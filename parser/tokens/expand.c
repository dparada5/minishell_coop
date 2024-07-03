/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:37:30 by dparada           #+#    #+#             */
/*   Updated: 2024/07/02 15:38:41 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

static char	*val_error(t_minishell *minishell, char *line, int *i, int l)
{
	char	*new_string;
	char	*val;
	int		j;

	j = 0;
	val = ft_itoa(minishell->val_error);
	new_string = malloc(((ft_strlen(line) - 2) + \
	ft_strlen(val) + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	if (line[0] != '$')
	{
		while (j < *i)
			new_string[l++] = line[j++];
	}
	j = 0;
	while (val[j])
		new_string[l++] = val[j++];
	j = *i + 2;
	while (line[j])
		new_string[l++] = line[j++];
	new_string[l] = '\0';
	minishell->val_error = 0;
	*i += ft_strlen(val);
	return (new_string);
}

static char	*get_var(char *line, int *i, int len, t_minishell *minishell)
{
	int		j;
	int		l;
	char	*aux;

	j = *i + 1;
	l = 0;
	while (line[j])
	{
		if (ft_isalnum(line[j]) == 0 && line[j] != '_')
			break ;
		len++;
		j++;
		l++;
	}
	aux = malloc(sizeof(char) * (l + 1));
	if (!aux && minishell->flag == 0)
		msj_error(MALLOC_FAILED, minishell, 0);
	j = *i;
	l = 0;
	while (++j <= len)
		aux[l++] = line[j];
	aux[l] = '\0';
	return (aux);
}

static char	*check_var(t_minishell *minishell, char *line, \
t_env *aux_env, int *i)
{
	char	*aux;
	char	*new_string;

	if (ft_strcmp(line, "~") == 0)
		line = ft_strdup("$HOME");
	else if (line[*i - 1] != '\\' && line[*i] == '~')
	{
		(*i)++;
		return (line);
	}
	aux = get_var(line, i, *i, minishell);
	aux_env = ft_get_envvar(minishell->env, aux);
	if (line[(*i) - 1] == '\\')
		new_string = is_not_expandable(line, i - 1);
	else if (line[*i + 1] == '~')
		new_string = is_not_expandable(line, i);
	else if (line[*i + 1] == '?')
		new_string = val_error(minishell, line, i, 0);
	else if (!aux_env)
		new_string = does_not_exist(line, aux, i);
	else
		new_string = expand(line, aux_env, i, 0);
	if (!new_string && minishell->flag != 1)
		msj_error(MALLOC_FAILED, minishell, 0);
	return (new_string);
}

char	*expansion(char *line, t_minishell *minishell)
{
	int	i;

	if (minishell->flag != 1)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '~' || line[i] == '$')
				line = check_var(minishell, line, NULL, &i);
			else
				i++;
		}
	}
	return (line);
}

void	check_expansion(t_token *token, t_minishell *minishell)
{
	t_token	*aux;

	aux = token;
	if (minishell->flag != 1)
	{
		while (aux)
		{
			if (aux->token == T_W || aux->token == T_DQ)
				aux->content = expansion(aux->content, minishell);
			aux = aux->next;
		}
	}
}
