/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:11:05 by dparada           #+#    #+#             */
/*   Updated: 2024/07/12 12:33:48 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

t_env	*ft_get_envvar(t_env *env, char *var_name)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		if (ft_strcmp(aux->key, var_name) == 0)
			return (aux);
		aux = aux->next;
	}
	return (NULL);
}

int	ft_change_envvar(t_env *env, char *var_name, char *new_value)
{
	t_env	*aux;

	aux = ft_get_envvar(env, var_name);
	if (!aux)
		return (0);
	free (aux->content);
	aux->content = ft_strdup(new_value);
	return (1);
}

void	ft_swap_envnodes(t_env *prev, t_env *act, t_env *next, t_env *last)
{
	prev->next = next;
	next->next = act;
	act->next = last;
}

t_env	*new_env_exp(char *key, char *content)
{
	t_env	*env;

	env = malloc (sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	if (content)
		env->content = ft_strdup(content);
	if ((!env->content && content) || !env->key)
		return (NULL);
	env->equal = 0;
	env->next = NULL;
	return (env);
}
