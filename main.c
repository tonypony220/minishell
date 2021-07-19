#include "minishell.h"

int		_start_shell(t_shell *shell)
{
	char *line;

	shell->status = 1;
	while (shell->status)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, do_signals);
		line = readline("["SHELL_NAME"]# ");
		if (line == NULL)
			return (1);
		shell->err = 0;	
		if (ft_strncmp(line, "exit", ft_strlen(line) + 1) == 0)
			shell->status = 0;
		shell->flags = _init_flags();
		if (pre_parser(line, shell))
		{
			add_history(line);
//			print_command(shell); // Print for testing
			if (!shell->err)
				execute(shell);
		}
		/* < add free for heredoc buffer */
		if (shell->heredoc)
			free(shell->heredoc);
		shell->heredoc = NULL;


//		if (shell->cmd);
		ft_lstclear(&shell->cmd, free_process); // protected pointer cmd 
		if (line)
			free(line);
	}
	ft_lstclear(&shell->env, del_dict);
	return (1);
}

t_flags	_init_flags(void)
{
	t_flags	flags;

	ft_memset((void*)&flags, 0, sizeof(flags));
	flags.pipe_in = -1;
	flags.pipe_out = -1;
	return (flags);
}

int _main(int ac, char **av, char **envp)
{
	//struct vars;
	t_shell	shell;

	ft_bzero(&shell, sizeof(shell));
	upload_env_to_dict(envp, &shell.env);
	_start_shell(&shell);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	return(_main(ac, av, envp));
//	int i = 1000;
//
//	while (i--)
//	{
//		struct process *ps = (struct process*)ft_calloc(sizeof(struct process), 1);
//		printf("%p[%d %d]\n", ps->fd, ps->fd[0], ps->fd[1]);	
//		if (ps->filed[0] || ps->filed[1])
//			printf("%p[%p %p]\n", ps->filed, ps->filed[0], ps->filed[1]);	
//	}
}
