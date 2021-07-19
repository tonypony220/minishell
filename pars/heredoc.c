#include "../minishell.h"

int		g_heredoc_status;

int		heredoc_comp(t_shell *shell, char *stop)
{
	struct process *new;

	if (heredoc_test(shell, stop))
	{
		new = (struct process*)ft_calloc(1, sizeof(*new));
		if (new == NULL)
			return (-1);
		new->args = (char **)ft_calloc(2, sizeof(char *));
		if (new->args == NULL)
			return (-1);
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

int		heredoc_init(t_shell *shell, char *stop)
{
	g_heredoc_status = 1;
	if (shell->heredoc)
		free(shell->heredoc);
	shell->heredoc = NULL;
	shell->flags.heredoc = 1;
	shell->flags.double_q = 1;
	heredoc_comp(shell, stop);
	return (1);
}

/* void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_heredoc_status = 0;
		write(1, 0x03, 1);
		//rl_on_new_line();
  		rl_replace_line("\n", 0);
		//rl_redisplay();
		rl_done = 1;
	}
} */

void		do_signals(int sig)
{
	if (sig == SIGINT && !g_heredoc_status)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGINT && g_heredoc_status)
	{
		g_heredoc_status = 0;
		rl_replace_line("", 0);
		rl_redisplay();
		//rl_done = 1;
	}
}

int		finish_heredoc(t_shell *shell, char *line)
{
	if (g_heredoc_status)
	{	
		if (line)
			free(line);
		shell->heredoc = token_strjoin(shell->heredoc, "");
	}
	else
	{
		shell->err = -1;
		return (1);
	}
	return (1);
}

int	heredoc_test(t_shell *shell, char *stop)
{
	char	*line;

	line = NULL;
	while (g_heredoc_status)
	{
		//signal(SIGINT, SIG_IGN);
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
