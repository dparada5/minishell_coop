
#include "./../../../inc/minishell.h"

void	ft_free_mat(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i])
		free (mat[i]);
	free (mat);
}
