
#include "./../../inc/minishell.h"
//912

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	(void)argv;
	if (argc == 1)
	{
		minishell = malloc(sizeof(t_minishell));
		if (!minishell)
			msj_error(MALLOC_FAILED, minishell, 0);
		init_ev_exp(minishell, env);
		// init_signal();
		init_minishell(minishell);
	}
}