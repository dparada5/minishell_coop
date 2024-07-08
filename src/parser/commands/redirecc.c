
#include "./../../../inc/minishell.h"

void	msj_error_fd(int val, char *str, t_cmds *cmds, t_minishell *minishell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	cmds->error = 1;
	minishell->val_error = val;
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
		cmds->executor = 1;
	}
	return (token);
}
