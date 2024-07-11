
#include "./../../inc/minishell.h"
//912

int	g_value;

void	init_ev_exp(t_minishell *minishell, char **env)
{
	if (env[0] == NULL)
		msj_error("Error: no environment found\n", minishell, 2);
	if (env[0] != NULL)
	{
		minishell->env = save_env(env, -1, minishell);
		minishell->exp = save_env(env, -1, minishell);
	}
	else
	{
		minishell->env = NULL;
		minishell->exp = NULL;
	}
	minishell->val_error = 0;
}

void	check_line(t_minishell *minishell)
{
	states(minishell->line, minishell);
	minishell->tokens = get_tokens(minishell->line, minishell);
	//printf_tokens(minishell->tokens);
	check_expansion(minishell->tokens, minishell);
	token_actions(minishell);
	// printf_cmds(minishell->cmds);
}

void	init_minishell(t_minishell *minishell)
{
	while (minishell->line)
	{
		minishell->cmd_empty = 0;
		if (!ft_strlen(minishell->line))
		{
			minishell->line = readline("minishell$ ");
			if (!minishell->line)
				control_d(minishell);
			continue ;
		}
		add_history(minishell->line);
		check_line(minishell);
		if (minishell->flag != 1)
		{
			signal(SIGQUIT, control_backslash);
			ft_executor(minishell);
		}
		ft_free_minishell(minishell, 0);
		g_value = 1;
		signal(SIGQUIT, SIG_IGN);
		minishell->line = readline("minishell$ ");
	}
	rl_clear_history();
}
