#include "./../../../inc/minishell.h"

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("error at getcwd()");
	ft_printf("%s\n", cwd);
	free (cwd);
}
