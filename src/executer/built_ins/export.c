
#include "./../../../inc/minishell.h"

void	ft_print_exp(t_env *exp)
{
	t_env *runner;

	runner = exp;
	while (runner)
	{
		ft_printf("declare -x %s", runner->key);
		if (!runner->equal)
		{
			ft_printf("=\"");
			if (runner->content)
				ft_printf("%s",runner->content);
			ft_printf("\"");
		}
		ft_printf("\n");
		runner = runner->next;
	}
}

void	ft_export_print(t_env **exp, t_env *prev_node, t_env *swap_aux, t_env *run)
{
	run = *exp;
	while (run)
	{
		if (run->next && ft_strncmp(run->key, run->next->key, ft_strlen(run->key)) > 0)
		{
			if (!prev_node)
			{
				swap_aux = run->next->next;
				*exp = run->next;
				run->next->next = run;
				run->next = swap_aux;
			}
			else
				ft_swap_envnodes(prev_node, run, run->next, run->next->next);
			prev_node = NULL;
			run = *exp;
		}
		else
		{
			prev_node = run;	
			run = run->next;
		}
	}
	ft_print_exp(*exp);
}

void	ft_check_and_replace(t_minishell *mshll, char *key, char *content)
{
	t_env	*aux;

	if (!ft_get_envvar(mshll->exp, key))
	{
		ft_lstadd_back_env(&(mshll->exp), new_env_exp(key, content));
		ft_lstadd_back_env(&(mshll->env), new_env_exp(key, content));
		aux = ft_get_envvar(mshll->exp, key);
		aux->equal = 0;
	}
	else
	{
		ft_change_envvar(mshll->env, key, content);
		ft_change_envvar(mshll->exp, key, content);
		aux = ft_get_envvar(mshll->exp, key);
		aux->equal = 0;
	}
}

int	ft_check_first_digit(char *str, t_minishell *mshll)
{
	if (!ft_isdigit(str[0]))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		mshll->val_error = 1;
		mshll->flag = 1;
		return (1);
	}
	return (0);
}

void	ft_export_insert(t_minishell *mshll, char *str, t_env *aux, int i)
{
	char	*key;
	char	*content;

	if (!ft_check_first_digit(str, mshll))
	{
		if (ft_strchr(str, '=') == NULL)
		{
			if (!ft_get_envvar(mshll->exp, str))
			{
				ft_lstadd_back_env(&(mshll->exp), new_env_exp(str, NULL));
				aux = ft_get_envvar(mshll->exp, str);
				aux->equal = 1;
			}
		}
		else
		{
			while (str[i] != '=')
				i++;
			key = ft_substr(str, 0, i);
			content = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
			ft_check_and_replace(mshll, key, content);
			free(key);
			free(content);
		}
	}
}
