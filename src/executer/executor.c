
#include "./../../inc/minishell.h"

int	ft_check_for_builtins(t_minishell *mshll, t_cmds *cmd)
{
	char	**cmds_flags;
	int		len;

	cmds_flags = cmd->cmds_flags;
	len = ft_strlen(cmds_flags[0]);
	if (ft_strncmp(cmds_flags[0], "cd", len) == 0)
		ft_cd(mshll, mshll->env, 0);
	else if (ft_strncmp(cmds_flags[0], "echo", len) == 0)
		ft_echo(mshll->cmds);
	else if (ft_strncmp(cmds_flags[0], "env", len) == 0)
		ft_env(mshll->env);
	else if (ft_strncmp(cmds_flags[0], "exit", len) == 0)
		ft_exit(0, mshll, cmd);
	else if (ft_strncmp(cmds_flags[0], "export", len) == 0 && !cmds_flags[1])
		ft_export_print(&mshll->exp, NULL, NULL, NULL);
	else if (ft_strncmp(cmds_flags[0], "export", len) == 0 && cmds_flags[1])
		ft_export_insert(mshll, cmds_flags[1], NULL, 0);
	else if (ft_strncmp(cmds_flags[0], "pwd", len) == 0)
		ft_pwd();
	else if (ft_strncmp(cmds_flags[0], "unset", len) == 0)
		ft_unset(mshll, cmds_flags[1]);
	else
		return (0);
	return (1);
}

void	ft_kindergarden(t_minishell *mshll, t_cmds *cmd, int *pipe_fd, int in_fd)
{
	char	*exec_path;

	if (!ft_strlen(cmd->cmds) && cmd->executor == 1)
		ft_free_and_exit(mshll, 127, NULL, 1);
	if (!cmd->index)
		close(pipe_fd[0]);
	if (!cmd->next)
		close(pipe_fd[1]);
	if (cmd->fd_in != 0)
		dup2(cmd->fd_in, 0);
	else
		dup2(in_fd, 0);
	if (cmd->fd_out != 1)
		dup2(cmd->fd_out, 1);
	else if (cmd->next)
		dup2(pipe_fd[1], 1);
	if (ft_check_for_builtins(mshll, cmd))
		ft_free_and_exit(mshll, 0, NULL, 1);
	exec_path = ft_get_exec_path(mshll, cmd->cmds);
	ft_save_env_mat(mshll, -1, 0);
	execve(exec_path, cmd->cmds_flags, 0);
	ft_free_and_exit(mshll, 127, "command not found", 1);
}

void	ft_single_cmd(t_minishell *mshll, t_cmds *cmd, int fd_in)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (!ft_strlen(cmd->cmds) && cmd->executor == 1)
		return(ft_free_and_exit(mshll, 127, NULL, 0));
	if (fd_in != 0)
		dup2(cmd->fd_in, 0);
	if (cmd->fd_out != 1)
		dup2(cmd->fd_out, 1);
	if (!ft_check_for_builtins(mshll, cmd))
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
			mshll->val_error = ft_wait();
		}
	}
}

void	ft_bedroom(t_minishell *mshll, int	pipes_left, int in_fd)
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
		in_fd = pipe_fd[0];
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
//toma un puto cambio

