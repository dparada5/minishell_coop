
#include "./../../../inc/minishell.h"

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
