/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:50:58 by dparada           #+#    #+#             */
/*   Updated: 2024/06/28 17:06:33 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

static char	**ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	return (NULL);
}

void	ft_lstclear_cmds(t_cmds *lst)
{
	t_cmds	*aux;

	while (lst)
	{
		aux = lst;
		lst = lst->next;
		if (aux->cmds)
			free(aux->cmds);
		if (aux->fd_in != 0)
			close(aux->fd_in);
		if (aux->fd_out != 1)
			close(aux->fd_out);
		if (aux->heredoc == 1)
			unlink(".here_doc.tmp");
		aux->cmds = NULL;
		if (aux->cmds_flags)
			aux->cmds_flags = ft_free_matrix(aux->cmds_flags);
		free(aux);
		aux = NULL;
	}
	free(lst);
	lst = NULL;
}

void	ft_lstclear_token(t_token *lst)
{
	t_token	*aux;

	aux = lst;
	while (lst)
	{
		aux = lst;
		lst = lst->next;
		free(aux->content);
		aux->content = NULL;
		free(aux);
		aux = NULL;
	}
}

void	ft_lstclear_env(t_env *lst)
{
	t_env	*aux;

	aux = lst;
	while (lst)
	{
		aux = lst;
		lst = lst->next;
		free (aux->key);
		free (aux->content);
		aux->key = NULL;
		aux->content = NULL;
		free (aux);
		aux = NULL;
	}
}

void	ft_free_minishell(t_minishell *minishell, int bool)
{
	if (minishell->tokens || minishell->cmds || minishell->env)
	{
		if (minishell->tokens != NULL)
			ft_lstclear_token(minishell->tokens);
		if (minishell->cmds != NULL)
			ft_lstclear_cmds(minishell->cmds);
		if (minishell->line)
			free(minishell->line);
		minishell->line = NULL;
		minishell->flag = 0;
		if (bool == 1)
		{
			if (minishell->env)
				ft_lstclear_env(minishell->env);
			if (minishell->exp)
				ft_lstclear_env(minishell->exp);
		}
	}
	if (bool == 1)
		free(minishell);
}
