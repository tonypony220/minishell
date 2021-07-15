#include "../minishell.h"

int		exec_heredoc(struct process *ps)
{
	int fd[2];

	pipe(fd);
	write(fd[1], ps->shell->heredoc, ft_strlen2(ps->shell->heredoc));
	close(fd[1]);
	dup2(fd[0], ps->fd[IN]);
	close(fd[0]);
	return (1);
}

int	heredoc_test(t_shell *shell, char *stop, struct process *ps)
{
	char	*line;

	line = NULL;
	/* < add free for heredoc buffer */
	shell->flags.heredoc = 1;
	shell->flags.double_q = 1;
	ps->status |= (DIRECT | HEREDOC);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return (printf("bash: warning: here-document delimited by end-of-file (wanted `%s')\n", stop)); // bash warning
		if (ft_strcmp(line, stop) == 0)
		{
			free(line);
			return (1);
		}
		check_for_env(&line, shell);
		shell->heredoc = token_strjoin(shell->heredoc, line);	// NEED TO BE FREED	
		shell->heredoc = token_strjoin(shell->heredoc, "\n"); 
		if (line)
			free(line);
	}
	ps->args[0] = shell->heredoc;
	return (1);
}
