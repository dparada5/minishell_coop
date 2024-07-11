#include "./../../../inc/minishell.h"

int	ft_pipes_count(t_minishell *mshll)
{
	t_token	*runner;
	int		pipes;

	runner = mshll->tokens;
	pipes = 0;
	while (runner)
	{
		if (runner->token == T_P)
			pipes++;
		runner = runner->next;
	}
	return (pipes);
}
