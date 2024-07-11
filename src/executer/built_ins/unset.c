#include "./../../../inc/minishell.h"

void	ft_check_and_delete(t_env **envxp, char *key)
{
	t_env	*previous;
	t_env	*runner;
	int		index;

	index = 0;
	runner = *envxp;
	while (runner)
	{
		if (!ft_strncmp(runner->key, key, ft_strlen(key)))
		{
			if (index == 0)
				*envxp = runner->next;
			else
				previous->next = runner->next;
			free(runner->content);
			free(runner->key);
			free(runner);
			break ;
		}
		previous = runner;
		runner = runner->next;
		index++;
	}
}

void	ft_unset(t_minishell *mshll, char *key_to_delete)
{
	ft_check_and_delete(&(mshll->env), key_to_delete);
	ft_check_and_delete(&(mshll->exp), key_to_delete);
}
