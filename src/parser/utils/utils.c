
#include "./../../../inc/minishell.h"

void	msj_error(char *str, t_minishell *minishell, int val_error)
{
	if (errno)
	{
		perror(str);
		minishell->val_error = WEXITSTATUS(errno);
	}
	else
	{
		if (str)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
		}
		minishell->val_error = val_error;
	}
	minishell->flag = 1;
}

int	is_join(t_token *tokens)
{
	if (tokens && (tokens->token == T_W \
	|| tokens->token == T_DQ || tokens->token == T_SQ))
	{
		if (tokens->content && tokens->flag == 1)
			return (1);
	}
	else
		return (2);
	return (0);
}
