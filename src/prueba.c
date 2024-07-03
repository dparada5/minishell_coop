// #include "../inc/minishell.h"

// t_token	*here_doc(t_token *token, t_cmds *cmds, t_minishell *minishell)
// {
// 	int		fd;
// 	char	*line;

// 	if (cmds->error == 0)
// 	{
// 		if (cmds->fd_in != 0)
// 			close(cmds->fd_in);
// 		if (SIGINT)
// 			minishell->flag = 1;
// 		// signal(SIGINT, control_c_hd);
// 		fd = open (".here_doc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 		if (fd < 0)
// 			msj_error(1, ERROR_FD, cmds, minishell);
// 		line = readline("> ");
// 		while (line && minishell->flag != 1)
// 		{
// 			if (ft_strcmp(line, token->content) == 0 || !line)
// 			{
// 				free(line);
// 				break ;
// 			}
// 			check_heredoc_line(line, minishell, fd);
// 			line = readline("> ");
// 			if (SIGINT)
// 				minishell->flag = 1;
// 		}
// 		close (fd);
// 		cmds->fd_in = open (".here_doc.tmp", O_RDONLY);
// 		cmds->heredoc = 1;
// 	}
// 	return (token);
// }
