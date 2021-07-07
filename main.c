#include "minishell.h"
#include "mini_shell/mini_parser.h"

int		start_shell(t_shell *shell)
{
	char *line;

	shell->status = 1;
	while (shell->status)
	{
		line = readline("["SHELL_NAME"]#");
		shell->err = 0;
		if (ft_strncmp(line, "exit", ft_strlen(line) + 1) == 0)
			shell->status = 0;
		shell->flags = init_flags();
		if (pre_parser(line, shell))
		{
			add_history(line);
			execute(shell->vars);
			//mini_exec(&line, shell);
		}
		ft_lstclear(&shell->token);
		free(line);
	}
	ft_lstclear(shell->vars->env, del_dict);
	//ft_env_clear(&shell->env);
	return (1);
}

t_flags	init_flags(void)
{
	t_flags	flags;

	ft_memset(flags, 0, sizeof(flags));
	flags.semi_colon = 1;
	flags.pipe_in = -1;
	flags.pipe_out = -1;
	return (flags);
}

int _main(int ac, char **av, char **envp)
{
	struct vars;
	t_shell	shell;

	ft_memset(vars, 0, sizeof(vars));
	ft_memset(vars.shell, 0, sizeof(vars.shell));
	vars.shell->vars = &vars;
	upload_env_to_dict(envp, vars.env);
	//init_env(envp, &shell);
	start_shell(&shell);
}

int	main(int ac, char **av, char **envp)
{
	_main(ac, av, envp);
	return (0);
}
