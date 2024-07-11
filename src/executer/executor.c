/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:11:14 by dparada           #+#    #+#             */
/*   Updated: 2024/07/11 14:36:44 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

int	ft_built(t_minishell *ms, t_cmds *cmd, char **cmd_f)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd_f[0], "cd", 3) == 0 && !cmd->cmds_flags[2])
		ft_cd(ms, ms->env, 0);
	else if (ft_strncmp(cmd_f[0], "cd", 3) == 0 && cmd->cmds_flags[2])
		msj_error("cd: too many arguments\n", ms, 1);
	else if (ft_strncmp(cmd_f[0], "echo", 5) == 0)
		ft_echo(ms->cmds);
	else if (ft_strncmp(cmd_f[0], "env", 4) == 0)
		ft_env(ms->env, ms, cmd_f[1]);
	else if (ft_strncmp(cmd_f[0], "exit", 5) == 0)
		ft_exit(0, ms, cmd);
	else if (ft_strncmp(cmd_f[0], "export", 6) == 0 && !cmd_f[1])
		ft_check_invalid_export(ms, cmd, 0);
	else if (ft_strncmp(cmd_f[0], "export", 7) == 0 && cmd_f[1])
		ft_check_invalid_export(ms, cmd, 1);
	else if (ft_strncmp(cmd_f[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd_f[0], "unset", 6) == 0)
		while (cmd_f[++i])
			ft_unset(ms, cmd_f[i]);
	else
		return (ms->val_error = 0, 0);
	return (ms->val_error = 0, 1);
}

void	ft_kindergarden(t_minishell *ms, t_cmds *cmd, int *pipe_fd, int in_fd)
{
	char	*exec_path;

	if (!ft_strlen(cmd->cmds) && cmd->executor == 1)
		ft_free_and_exit(ms, 0, NULL, 1);
	if (!cmd->index)
		close(pipe_fd[0]);
	if (!cmd->next)
		close(pipe_fd[1]);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		ft_free_and_exit(ms, 0, NULL, 1);
	else if (cmd->fd_in != 0)
		dup2(cmd->fd_in, 0);
	else
		dup2(in_fd, 0);
	if (cmd->fd_out != 1)
		dup2(cmd->fd_out, 1);
	else if (cmd->next)
		dup2(pipe_fd[1], 1);
	if (ft_built(ms, cmd, cmd->cmds_flags))
		ft_free_and_exit(ms, 0, NULL, 1);
	exec_path = ft_get_exec_path(ms, cmd->cmds);
	ft_save_env_mat(ms, -1, 0);
	execve(exec_path, cmd->cmds_flags, 0);
	ft_free_and_exit(ms, 127, "command not found", 1);
}

void	ft_single_cmd(t_minishell *mshll, t_cmds *cmd, int fd_in)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (!ft_strlen(cmd->cmds) && cmd->executor == 1)
		return (ft_free_and_exit(mshll, 0, NULL, 0));
	if (fd_in != 0)
		dup2(cmd->fd_in, 0);
	if (cmd->fd_out != 1)
		dup2(cmd->fd_out, 1);
	if (!ft_built(mshll, cmd, cmd->cmds_flags))
	{
		if (pipe(pipe_fd) == -1)
			msj_error("pipe error\n", mshll, 1);
		pid = fork();
		if (pid == -1)
			return (msj_error("Error ar fork() function.", mshll, 2));
		if (pid == 0)
			ft_kindergarden(mshll, cmd, pipe_fd, fd_in);
		else
		{
			close(pipe_fd[1]);
			close(pipe_fd[0]);
			mshll->val_error = ft_wait();
		}
	}
}

void	ft_bedroom(t_minishell *mshll, int pipes_left, int in_fd)
{
	int		pipe_fd[2];
	pid_t	pid;
	t_cmds	*runner;

	runner = mshll->cmds;
	while (--pipes_left >= 0)
	{
		if (pipe(pipe_fd) == -1)
			msj_error("pipe error\n", mshll, 1);
		pid = fork();
		if (pid == -1)
			return (msj_error("Error ar fork() function.", mshll, 2));
		if (pid == 0)
			ft_kindergarden(mshll, runner, pipe_fd, in_fd);
		else
		{
			close(pipe_fd[1]);
			mshll->val_error = ft_wait();
		}
		runner = runner->next;
		close(in_fd);
		in_fd = dup(pipe_fd[0]);
		close(pipe_fd[0]);
	}
}

void	ft_executor(t_minishell *mshll)
{
	int		pipes;
	int		in_fd;
	int		stin;
	int		stout;

	g_value = 2;
	stin = dup(STDIN_FILENO);
	stout = dup (STDOUT_FILENO);
	pipes = ft_pipes_count(mshll);
	ft_set_cmds_index(mshll);
	in_fd = mshll->cmds->fd_in;
	if (!pipes)
		ft_single_cmd(mshll, mshll->cmds, in_fd);
	else
		ft_bedroom(mshll, pipes + 1, in_fd);
	dup2(stin, STDIN_FILENO);
	dup2(stout, STDOUT_FILENO);
}
