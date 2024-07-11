/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:10:16 by dparada           #+#    #+#             */
/*   Updated: 2024/07/11 14:10:18 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

int	ft_cd_dir(char	*pre_path, char *end_path, t_env *env, t_minishell *mshll)
{
	char	*aux;
	int		return_value ;
	char	*absolute_path;
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = ft_get_envvar(env, "PWD");
	oldpwd = ft_get_envvar(env, "OLDPWD");
	absolute_path = ft_strdup(end_path);
	aux = ft_strjoin(pre_path, end_path);
	return_value = chdir(aux);
	free (aux);
	if (return_value == -1)
	{
		return_value = chdir(absolute_path);
		if (return_value != -1)
			ft_update_pwds(env, pwd->content, absolute_path);
	}
	else
		ft_update_pwds(env, pwd->content, aux);
	if (return_value == -1)
		if (ft_cd_norm(mshll, absolute_path))
			return (return_value);
	return (free(absolute_path), return_value);
}

int	ft_pwds_chdir(t_env *env, char *n_pwd, char *n_opwd, t_minishell *ms)
{
	int		error_check;

	error_check = chdir(n_pwd);
	if (error_check == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(n_pwd, 2);
		msj_error(" ", ms, 1);
	}
	else
	{
		ft_change_envvar(env, "OLDPWD", n_opwd);
		ft_change_envvar(env, "PWD", n_pwd);
	}
	return (error_check);
}

int	ft_cd(t_minishell *ms, t_env *env, int error_)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*aux_join;
	char	*aux_pwd;
	char	*new_dir;

	pwd = ft_get_envvar(env, "PWD");
	oldpwd = ft_get_envvar(env, "OLDPWD");
	new_dir = ms->cmds->cmds_flags[1];
	if (!new_dir)
		new_dir = ft_get_envvar(env, "HOME")->content;
	if (!new_dir)
		error_ = ft_pwds_chdir(env, new_dir, pwd->content, ms);
	else if (!ft_strncmp("-", new_dir, ft_strlen(new_dir)))
	{
		aux_pwd = ft_strdup(oldpwd->content);
		error_ = ft_pwds_chdir(env, aux_pwd, pwd->content, ms);
		free (aux_pwd);
	}
	else
	{
		aux_join = ft_strdup(pwd->content);
		error_ = ft_cd_dir(ft_strjoin(aux_join, "/"), new_dir, env, ms);
	}
	return (error_);
}
