#include "./../../../inc/minishell.h"

void	ft_env(t_env *env, t_minishell *mshll, char *flag)
{
	t_env	*aux;

	if (flag)
	{
		msj_error("env: '", mshll, 127);
		ft_putstr_fd(flag, 2);
		ft_putstr_fd("': No such file or directory.\n", 2);
	}
	else
	{
		aux = env;
		while (aux)
		{
			ft_putstr_fd(aux->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(aux->content, 1);
			aux = aux->next;
		}
	}
}
