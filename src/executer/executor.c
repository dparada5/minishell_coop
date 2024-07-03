
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
		ft_exit(0, mshll);
	else if (ft_strncmp(cmds_flags[0], "export", len) == 0 && !cmds_flags[1])
		ft_export_print(&mshll->exp, NULL, NULL, NULL);
	else if (ft_strncmp(cmds_flags[0], "export", len) == 0 && cmds_flags[1])
		ft_export_insert(mshll, cmds_flags[1]);
	else if (ft_strncmp(cmds_flags[0], "pwd", len) == 0)
		ft_pwd();
	else if (ft_strncmp(cmds_flags[0], "unset", len) == 0)
		ft_unset(mshll, cmds_flags[1]);
	else
		return (0);
	return (1);
}

// int	ft_choose_builtin_executor(t_minishell *mshll, t_cmds *cmd, pid_t pid)
// {
// 	if (!cmd->next && !cmd->index)
// 		if (pid != 0)
// 			return (ft_check_for_builtins(mshll, cmd));
// 	else if (pid == 0)
// 		return (ft_check_for_builtins(mshll, cmd));
// }
//void	ft_factory(t_minishell *mshll, )

void	ft_kindergarden(t_minishell *mshll, t_cmds *cmd, int *pipe_fd, int in_fd)
{
	char	*exec_path;

	if (!ft_strlen(cmd->cmds) && cmd->executor == 1)
		exit (0);//PORHACER comprobar si los hijos tiene que liberar la memoria de las estructuras o si eso es solo el padre
	if (!cmd->index)
		close(pipe_fd[0]);
	if (!cmd->next)
		close(pipe_fd[1]);
	if (cmd->fd_in != 0)
	{
		// ft_putendl_fd("Entra", 2);
		dup2(cmd->fd_in, 0);
	}
	else
		dup2(in_fd, 0);
	if (cmd->fd_out != 1)
		dup2(cmd->fd_out, 1);
	else if (cmd->next)
		dup2(pipe_fd[1], 1);
	exec_path = ft_get_exec_path(mshll, cmd->cmds);
	ft_save_env_mat(mshll, -1, 0);
	execve(exec_path, cmd->cmds_flags, 0);
	msj_error("cmd not found\n", mshll, 2);
	exit (0);
}

void	ft_bedroom(t_minishell *mshll, int	pipes_left)
{
	int		pipe_fd[2];
	pid_t	pid;
	t_cmds	*runner;
	int		in_fd;

	ft_set_cmds_index(mshll);
	runner = mshll->cmds;
	in_fd = runner->fd_in;
	while (pipes_left >= 0)
	{
		if (pipe(pipe_fd) == -1)
			msj_error("pipe error\n", mshll, 1);
		if (ft_check_for_builtins(mshll, runner))
			;//PORHACER comprobar si los hijos tiene que liberar la memoria de las estructuras o si eso es solo el padre
		else
		{
			pid = fork();
			if (pid == -1)
				return ;//PORHACER añadir gestión en este caso de error
			if (pid == 0)
				ft_kindergarden(mshll, runner, pipe_fd, in_fd);
			else
			{
				close(pipe_fd[1]);
				wait(0);
			}
		}
		runner = runner->next;
		in_fd = pipe_fd[0];
		pipes_left--;
	}
}

void	ft_executor(t_minishell *mshll)
{
	int	pipes;

	pipes = ft_pipes_count(mshll);
	ft_bedroom(mshll, pipes);
	// ft_free_minishell(mshll, 0);
}

