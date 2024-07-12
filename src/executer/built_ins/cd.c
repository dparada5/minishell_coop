/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:10:16 by dparada           #+#    #+#             */
/*   Updated: 2024/07/12 13:10:17 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

int	ft_cd_dir(char	*pre_path, char *end_path, t_minishell *ms, char *buff)
{
	char	*aux;
	int		return_value ;
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = ft_get_envvar(ms->env, "PWD");
	oldpwd = ft_get_envvar(ms->env, "OLDPWD");
	aux = ft_strjoin(pre_path, end_path);
	buff = getcwd(NULL, 4096);
	if (!buff)
		ft_free_and_exit(ms, 2, "Couldn't get current directory", 1);
	return_value = chdir(aux);
	if (return_value == -1)
	{
		return_value = chdir(end_path);
		if (return_value != -1)
			ft_update_pwds(ms->env, buff, end_path);
	}
	else
		ft_update_pwds(ms->env, buff, aux);
	if (return_value == -1)
		if (ft_cd_norm(ms, end_path))
			return (free(buff), free(aux), return_value);
	return (free (aux), free(buff), return_value);
}

int	ft_pwds_chdir(t_env *env, char *n_pwd, char *n_opwd, t_minishell *ms)
{
	int		error_check;
	char	*old_pwd;

	(void)n_opwd;
	old_pwd = getcwd(NULL, 4096);
	error_check = chdir(n_pwd);
	if (error_check == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(n_pwd, 2);
		msj_error(" ", ms, 1);
	}
	else
	{
		ft_change_envvar(env, "OLDPWD", old_pwd);
		ft_change_envvar(env, "PWD", n_pwd);
	}
	free(old_pwd);
	return (error_check);
}

char	*ft_cut_end(char *str)
{
	int		i;
	char	*dst;

	i = ft_strlen(str);
	while (str[i] && str[i] != '/')
		i--;
	dst = ft_substr(str, 0, i);
	return (dst);
}

int	ft_cd(t_minishell *ms, t_env *env, int error_, char *n_dir)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*aux_join;
	char	*aux_pwd;

	pwd = ft_get_envvar(env, "PWD");
	oldpwd = ft_get_envvar(env, "OLDPWD");
	if (!n_dir)
		n_dir = ft_strdup(ft_get_envvar(env, "HOME")->content);
	if (!ft_strncmp("-", n_dir, ft_strlen(n_dir)))
	{
		aux_pwd = ft_strdup(oldpwd->content);
		error_ = ft_pwds_chdir(env, aux_pwd, pwd->content, ms);
		free (aux_pwd);
	}
	else
	{
		aux_join = ft_strdup(pwd->content);
		error_ = ft_cd_dir(ft_strjoin(aux_join, "/"), n_dir, ms, NULL);
	}
	return (error_);
}
