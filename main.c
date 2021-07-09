#include "minishell.h"

int		_start_shell(t_shell *shell)
{
	char *line;

	shell->status = 1;
	while (shell->status)
	{
		line = readline("["SHELL_NAME"]#");
		shell->err = 0;
		if (ft_strncmp(line, "exit", ft_strlen(line) + 1) == 0)
			shell->status = 0;
		shell->flags = _init_flags();
		if (pre_parser(line, shell))
		{
			add_history(line);
			print_command(shell); // Print for testing
			execute(shell);
		}
		if (shell->cmd);
			//free_command(&shell->cmd);
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
	flags.semi_colon = 1;
	flags.pipe_in = -1;
	flags.pipe_out = -1;
	return (flags);
}

int _main(int ac, char **av, char **envp)
{
	//struct vars;
	t_shell	shell;

	//ft_memset(vars, 0, sizeof(vars));
	//ft_memset((void *)&shell, 0, sizeof(t_shell*));
	ft_bzero(&shell, sizeof(shell));
	//vars.shell->vars = &vars;
	upload_env_to_dict(envp, &shell.env);
	//init_env(envp, &shell);
	_start_shell(&shell);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	return(_main(ac, av, envp));
}
