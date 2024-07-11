#include "./../../../inc/minishell.h"

void	ft_env(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		ft_putstr_fd(aux->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(aux->content, 1);
		aux = aux->next;
	}
}
