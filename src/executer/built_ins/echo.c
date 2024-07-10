#include "./../../../inc/minishell.h"

void	ft_echo(t_cmds *cmd)
{
	int	nnl_flag;
	int	i;

	nnl_flag = 0;
	i = 1;
	if (!ft_strncmp(cmd->cmds_flags[1], "-n", 3))
	{
		nnl_flag = 1;
		i++;
		while (!ft_strncmp(cmd->cmds_flags[i], "-n", 3))
			i++;
	}
	while (cmd->cmds_flags[i])
	{
		ft_putstr_fd(cmd->cmds_flags[i], 1);
		if (cmd->cmds_flags[i + 1])
			write (1, " ", 1);
		i++;
	}
	if (!nnl_flag)
		ft_putstr_fd("\n", 1);
}
