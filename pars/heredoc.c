#include "../minishell.h"

int	heredoc_comp(t_shell *shell, char *stop)
{
	struct s_process	*new;

	if (heredoc_test(shell, stop))
	{
		new = (struct s_process *)ft_calloc(1, sizeof(*new));
		if (new == NULL)
			return (set_error(shell, -5));
		new->args = (char **)ft_calloc(2, sizeof(char *));
		if (new->args == NULL)
			return (set_error(shell, -5));
		new->status |= (BUILTIN | HEREDOC);
		new->args[0] = ft_strdup(shell->heredoc);
		free(shell->heredoc);
		new->env = shell->env;
		new->shell = shell;
		shell->heredoc = NULL;
		shell->flags.pipe_count++;
		shell->flags.pipe_out = shell->flags.pipe_in + 1;
		set_flags(new, shell);
		shell->flags.pipe_out++;
		ft_lstadd_back(&shell->cmd, ft_lstnew(new));
	}
	shell->flags.heredoc = 0;
	return (1);
}

int	heredoc_init(t_shell *shell, char *stop)
{
	if (shell->heredoc)
		free(shell->heredoc);
	shell->heredoc = NULL;
	shell->flags.heredoc = 1;
	shell->flags.double_q = 1;
	heredoc_comp(shell, stop);
	return (1);
}

int	finish_heredoc(t_shell *shell, char *line)
{
	if (line)
		free(line);
	shell->heredoc = token_strjoin(shell->heredoc, "");
	return (1);
}

int	heredoc_test(t_shell *shell, char *stop)
{
	char	*line;
	int pid; 
	int status;

	((pid = fork()) == -1) && err("fork failed");
	if (pid == CHILD_PID)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		line = NULL;
		while (1)
		{
			signal(SIGINT, SIG_IGN);
			line = readline("> ");
			if (line == NULL)
				return (finish_heredoc(shell, line));
			if (ft_strcmp(line, stop) == 0)
				return (finish_heredoc(shell, line));
			check_for_env(&line, shell);
			shell->heredoc = token_strjoin(shell->heredoc, line);
			shell->heredoc = token_strjoin(shell->heredoc, "\n");
			if (line)
				free(line);
		}
		return (finish_heredoc(shell, line));
	}
	else
	{
		waitpid(0, &status, 0);
	}
}
