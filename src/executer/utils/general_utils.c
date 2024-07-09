
#include "./../../../inc/minishell.h"

int	ft_check_for_builtins_cmp(t_cmds *cmd)
{
	char	**cmds_flags;
	int		len;

	cmds_flags = cmd->cmds_flags;
	len = ft_strlen(cmds_flags[0]);
	if (ft_strncmp(cmds_flags[0], "cd", len) == 0)
		return (1);
	else if (ft_strncmp(cmds_flags[0], "echo", len) == 0)
		return (1);
	else if (ft_strncmp(cmds_flags[0], "env", len) == 0)
		return (1);
	else if (ft_strncmp(cmds_flags[0], "exit", len) == 0)
		return (1);
	else if (ft_strncmp(cmds_flags[0], "export", len) == 0 && !cmds_flags[1])
		return (1);
	else if (ft_strncmp(cmds_flags[0], "export", len) == 0 && cmds_flags[1])
		return (1);
	else if (ft_strncmp(cmds_flags[0], "pwd", len) == 0)
		return (1);
	else if (ft_strncmp(cmds_flags[0], "unset", len) == 0)
		return (1);
	return (0);
}

void	ft_free_mat(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i])
		free (mat[i]);
	free (mat);
}

int	ft_is_num(char	*str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

int ft_wait(void)
{
    int status;
    int out_status;

    out_status = 0;
    wait(&status);
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        out_status = WEXITSTATUS(status);
    else if (WIFEXITED(status) && WIFSIGNALED(status) != 0)
        out_status = WTERMSIG(status);
    else
        out_status = 0;
    return (out_status);
}

void	ft_free_and_exit(t_minishell *mshll, int exit_value, char *error_msg)
{
	ft_free_minishell(mshll, 1);
	if (exit_value)
		msj_error(error_msg, mshll, exit_value);
	exit (exit_value);
}
