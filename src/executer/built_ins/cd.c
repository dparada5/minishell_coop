
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
		return_value = chdir(absolute_path);
	else
	{
		ft_change_envvar(env, "OLDPWD", pwd->content);
		ft_change_envvar(env, "PWD", aux);
	}
	if (return_value == -1)
		if (ft_cd_norm(mshll, absolute_path))
			return (return_value);
	return (free(absolute_path), return_value);
}

int	ft_pwds_chdir(t_env *env, char *new_pwd, char *new_oldpwd, t_minishell *mshll)
{
	int		error_check;

	error_check = chdir(new_pwd);
	if (error_check == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(new_pwd, 2);
		msj_error(" ", mshll, 1);
	}
	else
	{
		ft_change_envvar(env, "OLDPWD", new_oldpwd);
		ft_change_envvar(env, "PWD", new_pwd);
	}
	return (error_check);
}

int	ft_cd(t_minishell *mshll, t_env *env, int error_check)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*aux_join;
	char	*aux_pwd;
	char	*new_dir;

	pwd = ft_get_envvar(env, "PWD");
	oldpwd = ft_get_envvar(env, "OLDPWD");
	new_dir = mshll->cmds->cmds_flags[1];
	if (!new_dir)
		error_check = ft_pwds_chdir(env, ft_get_envvar(env, "HOME")->content, pwd->content, mshll);
	else if (!ft_strncmp("-", new_dir, ft_strlen(new_dir)))
	{
		aux_pwd = ft_strdup(oldpwd->content);
		error_check = ft_pwds_chdir(env, aux_pwd, pwd->content, mshll);
		free (aux_pwd);
	}
	else
	{
		aux_join = ft_strdup(pwd->content);
		error_check = ft_cd_dir(ft_strjoin(aux_join, "/"), new_dir, env, mshll);
	}
	return (error_check);
}
