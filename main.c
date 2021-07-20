#include "minishell.h"

void	do_signals(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/* add exit func */
int	_start_shell(t_shell *shell)
{
	while (shell->status)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, do_signals);
		shell->line = readline("["SHELL_NAME"]# ");
		if (shell->line == NULL)
			return (1);
		shell->err = 0;
		if (ft_strncmp(shell->line, "exit", ft_strlen(shell->line) + 1) == 0)
			shell->status = 0;
		shell->flags = _init_flags();
		if (pre_parser(shell->line, shell))
		{
			add_history(shell->line);
			if (!shell->err)
				handle_processes(shell->cmd, shell->env);
		}
		ft_lstclear(&shell->cmd, free_process);
		free_and_null(shell->heredoc, shell->line);
	}
	ft_lstclear(&shell->env, del_dict);
	return (1);
}

t_flags	_init_flags(void)
{
	t_flags	flags;

	ft_memset((void *)&flags, 0, sizeof(flags));
	flags.pipe_in = -1;
	flags.pipe_out = -1;
	return (flags);
}

int	_main(int ac, char **av, char **envp)
{
	t_shell	shell;

	ft_bzero(&shell, sizeof(shell));
	upload_env_to_dict(envp, &shell.env);
	shell.status = 1;
	_start_shell(&shell);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	return (_main(ac, av, envp));
}
