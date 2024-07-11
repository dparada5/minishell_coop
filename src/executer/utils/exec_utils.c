/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:11:08 by dparada           #+#    #+#             */
/*   Updated: 2024/07/11 14:11:09 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../inc/minishell.h"

char	*ft_get_exec_path(t_minishell *mshll, char *cmd)
{
	int		i;
	t_env	*path_var;
	char	**path_splitted;
	char	*exec_line;
	char	*join_aux;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	path_var = ft_get_envvar(mshll->env, "PATH");
	if (!path_var)
		msj_error("No path found", mshll, 130);
	path_splitted = ft_split(path_var->content, ':');
	i = -1;
	while (path_splitted[++i])
	{
		join_aux = ft_strjoin(path_splitted[i], "/");
		exec_line = ft_strjoin(join_aux, cmd);
		join_aux = NULL;
		if (access(exec_line, F_OK | X_OK) == 0)
			return (exec_line);
		free(exec_line);
		exec_line = NULL;
	}
	free(path_splitted);
	return (path_splitted = NULL, NULL);
}

void	ft_set_cmds_index(t_minishell *mshll)
{
	int		i;
	t_cmds	*cmd_runner;

	i = 0;
	cmd_runner = mshll->cmds;
	while (cmd_runner)
	{
		cmd_runner->index = i++;
		cmd_runner = cmd_runner->next;
	}
}

void	ft_check_invalid_export(t_minishell *mshll, t_cmds *cmd, int insert)
{
	int	i;

	i = 0;
	if (!insert)
	{
		if (!cmd->empty_flag)
			ft_export_print(&mshll->exp, NULL, NULL, NULL);
		else
			msj_error("export: `': not a valid identifier\n", mshll, 1);
	}
	else
	{
		if (cmd->empty_flag)
			msj_error("export: `': not a valid identifier\n", mshll, 1);
		while (cmd->cmds_flags[++i])
			ft_export_insert(mshll, cmd->cmds_flags[i], NULL, 0);
	}
}

int	ft_cd_norm(t_minishell *mshll, char *absol_path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(absol_path, 2);
	msj_error(" ", mshll, 1);
	free(absol_path);
	return (1);
}

void	ft_update_pwds(t_env *env, char *n_oldpwd, char *n_pwd)
{
	ft_change_envvar(env, "OLDPWD", n_oldpwd);
	ft_change_envvar(env, "PWD", n_pwd);
}
