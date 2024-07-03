/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:50:53 by dparada           #+#    #+#             */
/*   Updated: 2024/07/02 19:14:50 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

void	msj_error_fd(int val_error, char *str, t_cmds *cmds, t_minishell *minishell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	cmds->error = 1;
	minishell->val_error = val_error;
}

t_token	*open_append(t_token *token, t_cmds *cmds, t_minishell *minishell)
{
	token = token->next;
	if (cmds->error == 0)
	{
		if (cmds->fd_out != 1)
			close(cmds->fd_out);
		cmds->fd_out = open(token->content, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (cmds->fd_out < 0)
			msj_error_fd(2, ERROR_FD, cmds, minishell);
		cmds->heredoc = 0;
		cmds->executor = 1;
	}
	return (token);
}

t_token	*open_trunc(t_token *token, t_cmds *cmds, t_minishell *minishell)
{
	token = token->next;
	if (cmds->error == 0)
	{
		if (cmds->fd_out != 1)
			close(cmds->fd_out);
		cmds->fd_out = open(token->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (cmds->fd_out < 0)
			msj_error_fd(1, ERROR_FD, cmds, minishell);
		cmds->heredoc = 0;
		cmds->executor = 1;
	}
	return (token);
}

t_token	*open_infile(t_token *token, t_cmds *cmds, t_minishell *minishell)
{
	token = token->next;
	if (cmds->error == 0)
	{
		if (cmds->fd_in != 0)
			close(cmds->fd_in);
		cmds->fd_in = open(token->content, O_RDONLY);
		if (cmds->fd_in < 0)
			msj_error_fd(1, ERROR_FD, cmds, minishell);
		cmds->heredoc = 0;
		cmds->executor = 1;
	}
	return (token);
}

void	check_heredoc_line(char *line, t_minishell *minishell, int fd)
{
	ft_putendl_fd(expansion(line, minishell), fd);
	free(line);
}

t_token	*here_doc(t_token *token, t_cmds *cmds, t_minishell *minishell)
{
	int		fd;
	char	*line;

	if (cmds->error == 0)
	{
		if (cmds->fd_in != 0)
			close(cmds->fd_in);
		fd = open (".here_doc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			msj_error_fd(1, ERROR_FD, cmds, minishell);
		while (1)
		{
			line = readline("> ");
			if (ft_strcmp(line, token->content) == 0 || !line)
			{
				free(line);
				break ;
			}
			check_heredoc_line(line, minishell, fd);
		}
		close (fd);
		cmds->fd_in = open (".here_doc.tmp", O_RDONLY);
		cmds->heredoc = 1;
	}
	return (token);
}
