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

int		heredoc_comp(t_shell *shell, char *stop)
{
	struct process *new;

	if (heredoc_test(shell, stop))
	{
		new = (struct process*)ft_calloc(1, sizeof(*new));
		if (new == NULL)
			return (-1);
		new->args = (char **)ft_calloc(2 , sizeof(char *));
		if (new->args == NULL)
			return (-1);
		new->status |= (DIRECT | HEREDOC);
		new->args[0] = ft_strdup(shell->heredoc);
		free(shell->heredoc);
		shell->heredoc = NULL;
		shell->flags.pipe_count++;
		//printf("PIPE COUNT=[%d]\n", shell->flags.pipe_count);
		//if (shell->flags.has_pipe == 0)
		shell->flags.pipe_out = shell->flags.pipe_in + 1;
		set_flags(new, shell);
		shell->flags.pipe_out++;
		ft_lstadd_back(&shell->cmd, ft_lstnew(new));
	}
	shell->flags.heredoc = 0;
	return (1);
}

int	heredoc_test(t_shell *shell, char *stop)
{
	char	*line;

	line = NULL;
	/* < add free for heredoc buffer */
	if (shell->heredoc)
		free(shell->heredoc);
	shell->heredoc = NULL;

	shell->flags.heredoc = 1;
	shell->flags.double_q = 1;
	//ps->status |= (DIRECT | HEREDOC);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return (printf("bash: warning: here-document delimited by end-of-file (wanted `%s')\n", stop)); // bash warning
		if (ft_strcmp(line, stop) == 0)
		{
			free(line);
			if (shell->heredoc)
				return (1);
			return (0);
		}
		check_for_env(&line, shell);
		shell->heredoc = token_strjoin(shell->heredoc, line);	// NEED TO BE FREED	
		shell->heredoc = token_strjoin(shell->heredoc, "\n"); 
		if (line)
			free(line);
	}
	//ps->args[0] = shell->heredoc;
	return (1);
}
