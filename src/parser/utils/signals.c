
#include "./../../../inc/minishell.h"

void	control_c(int signal)
{
	(void)signal;
	if (g_value == 1)
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
	else if (g_value == 2)
		ft_putstr_fd("\n", 1);
}

void	control_d(t_minishell *minishell)
{
	ft_free_minishell(minishell, 1);
	ft_putstr_fd("exit\n", 1);
	exit(minishell->val_error);
}

void	control_backslash(int signal)
{
	(void)signal;
	if (g_value == 2)
		ft_putendl_fd("Quit (core dumped)", 2);
	// else
	// 	return ;
}

void	init_signal(void)
{
	signal(SIGINT, control_c);
	// if (g_value == 2)
	// else
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
