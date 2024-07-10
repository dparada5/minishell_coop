
#include "./../../../inc/minishell.h"

void	msj_error_fd(int val, char *str, t_cmds *cmds, t_minishell *minishell)
{
	if (!ft_pipes_count(minishell))
		minishell->flag = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(str, 2);
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
		if (access(token->content, F_OK | R_OK | W_OK | X_OK) == -1 && errno == EACCES)
		{
			// ft_putstr_fd("minishell: ", 2);
			msj_error_fd(1, token->content, cmds, minishell);
			cmds->fd_out = -1;
		}
		else
		{
			cmds->fd_out = open(token->content, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (cmds->fd_out < 0)
				msj_error_fd(2, ERROR_FD, cmds, minishell);
			cmds->executor = 1;
		}
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
		if (access(token->content, R_OK | W_OK) == -1 && errno == EACCES)
		{
			ft_putstr_fd("minishell: ", 2);
			msj_error_fd(1, token->content, cmds, minishell);
			cmds->fd_out = -1;
		}
		else
		{
			cmds->fd_out = open(token->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (cmds->fd_out < 0)
				msj_error_fd(1, ERROR_FD, cmds, minishell);
			cmds->executor = 1;
		}
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
		if (access(token->content, R_OK | W_OK) == -1 && errno == EACCES)
		{
			ft_putstr_fd("minishell: ", 2);
			msj_error_fd(1, token->content, cmds, minishell);
			cmds->fd_out = -1;
		}
		else
		{
			cmds->fd_in = open(token->content, O_RDONLY);
			if (cmds->fd_in < 0)
				msj_error_fd(1, ERROR_FD, cmds, minishell);
			cmds->executor = 1;
		}
	}
	return (token);
}
