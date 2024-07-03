
#include "./../../../inc/minishell.h"

int	ft_cd_dir(char	*pre_path, char *end_path, t_env *env)
{
	char	*aux;
	int		return_value ;
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = ft_get_envvar(env, "PWD");
	oldpwd = ft_get_envvar(env, "OLDPWD");
	aux = ft_strjoin(pre_path, end_path);
	// free (end_path);
	ft_change_envvar(env, "OLDPWD", pwd->content);
	ft_change_envvar(env, "PWD", aux);
	return_value = chdir(aux);
	free (aux);
	return (return_value);
}

//PORHACER arreglar que solo funciona en los casos que la dirección está dentro de la carpeta actual
int	ft_cd(t_minishell *minishell, t_env *env, int error_check)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*aux_join;
	char	*aux_pwd;
	char	*new_dir;

	pwd = ft_get_envvar(env, "PWD");
	oldpwd = ft_get_envvar(env, "OLDPWD");
	new_dir = minishell->cmds->cmds_flags[1];
	if (!new_dir)
	{
		ft_change_envvar(env, "OLDPWD", pwd->content);
		ft_change_envvar(env, "PWD", ft_get_envvar(env, "HOME")->content);
		error_check = chdir(pwd->content);
	}
	else if (!ft_strncmp("-", new_dir, ft_strlen(new_dir)))
	{
		aux_pwd = ft_strdup(oldpwd->content);
		ft_change_envvar(env, "OLDPWD", pwd->content);
		ft_change_envvar(env, "PWD", aux_pwd);
		free (aux_pwd);
		error_check = chdir(pwd->content);
	}
	else
	{
		aux_join = ft_strdup(pwd->content);
		error_check = ft_cd_dir(ft_strjoin(aux_join, "/"), new_dir, env);
	}
	return (error_check);
}
