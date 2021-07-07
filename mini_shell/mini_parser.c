#include "mini_parser.h"

void	single_quote(char *line, int i, t_shell *shell)
{
	int j;

	j = i;
	while(line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			shell->sq_err = 1;
			i++;
			while (line[i] != '\0')
			{
				if (line[i] == '\'')
				{
					shell->sq_err = 0;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	if (shell->sq_err == 1)
		error_out(shell, "syntax error single quotes");
}

void	double_quote(char *line, int i, t_shell *shell)
{
	int j;

	while(line[i] != '\0')
	{
		if (line[i] == '\"')
		{
			shell->dq_err = 1;
			i++;
			j = i;
			while (line[i] != '\0')
			{
				if (line[i] == '\"')
				{
					shell->dq_err = 0;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	if (shell->dq_err == 1 && shell->sq_err == 0)
		error_out(shell, "syntax error double quotes");
}

void	pipe_syntax(char *line, int i, t_shell *shell)
{
	int j;

	j = shell->i;
	while(line[shell->i] != '\0')
	{
		if (line[shell->i] == '\"')
		{
			shell->i++;
			while (line[shell->i] != '\"')
				shell->i++;
		}
		if (line[shell->i] == '\'')
		{
			shell->i++;
			while (line[shell->i] != '\'')
				shell->i++;
		}
		if (line[shell->i] == '|')
		{
			space_skip(line, shell);
		}
	}
	if (shell->dq_err == 1 && shell->sq_err == 0)
		error_out(shell, "syntax error double quotes");
}

int		check_cmd(char *line, t_shell *shell)
{
	int j;
	char qq;

	j = shell->i;
	single_quote(line, j, shell);
	double_quote(line, j, shell);
	//pipe_syntax(line, j, shell);
	shell->dq_err = 0;
	shell->sq_err = 0;
	shell->i = j;
	if (shell->err == -1)
		return (-1);
	return (1);
}

int	pre_env_check(char *line, t_shell *shell)
{
	int i;
	int end;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			end = i;
			i++;
			while (line[i] != ' ' && line[i] != '\'' && line[i] != '\"'
					&& line[i] != '\\' && line[i] != '$')
					i++;
			if (get_env(shell, line, end + 1, i - 1) == 0)
			{
				shell->env_sign = 0;
				free_env_shell(shell);
				return (0);
			}
			else
				return (1);
		}
		(i)++;
	}
	return (0);
}

int	check_for_env(char **line, t_shell *shell)
{
	int i;

	i = 0;
	shell->env_sign = 0;
	if (line[0][i + 1] == '\0' || shell->flags.double_q == 0) // SegFault with single $
		return (0);
	while (line[0][i] != '\0')
	{
		if (line[0][i] == '$')
		{
			shell->env_sign = 1;
/* 			if (pre_env_check(line[0], shell) == 0)
				return (0); */
			*line = add_env_to_str(line[0], shell);
		}
		i++;
	}
	if (shell->env_sign)
		check_for_env(line, shell);
	return (0);
}

char	*add_env_to_str(char *line, t_shell *shell)
{
	char *tmp;
	char *tmp2;
	char *env;
	int i;
	int end;

	i = 0;
	env = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			end = i++;
			tmp = ft_substr(line, 0, end);
			while (ft_strchr(" \'\"\\$;:|", line[i]) == 0)
					i++;
			tmp2 = ft_substr(line, i, ft_strlen(line) - i);
			if (get_env(shell, line, end + 1, i - 1) == 1)
				env = ft_strdup(shell->env_value);
			free_env_shell(shell);
			tmp = ft_strjoin(tmp, env);
			tmp = ft_strjoin(tmp, tmp2);
			free(env);
			free(tmp2);
			free(line);
			return (tmp);
		}
		(i)++;
	}
	return (line);
}

void	exec_check(t_shell *shell)
{
	if (ft_strncmp(shell->token->token, "env", 3) == 0)
		ft_env(shell);
}

void	check_for_pipe(char *line, t_shell *shell, t_list *token)
{
	int i;

	i = shell->i;
	shell->i++;
	space_skip(line, shell);
	if (line[shell->i] == '\0')
		shell->flags.pipe_out = -1;
	if (line[shell->i] == '|')
	{
		shell->flags.pipe_out++;
		compose_command(&shell->cmd, token, shell, ft_lstsize(token));
	}
	shell->i = i;
}

void	main_parser(char *line, t_shell *shell, t_list **token)
{
	while(line[shell->i] != '\0')
	{
		if (line[shell->i] == '\'')
			parse_single_quotes(line, shell);
		else if (line[shell->i] == '\"')
			parse_double_quotes(line, shell);
		else if (line[shell->i] == '$')
			parse_env_sign(line, shell);
/* 		else if (line[shell->i] == '>' || line[shell->i] == '<')
			parse_redirect(line, shell); */
		else if (line[shell->i] == '|')
			parse_pipe(line, shell);
		else
			parse_cmd(line, shell);
		if (line[shell->i + 1] == ' ' || line[shell->i + 1] == '\0')
		{
			ft_lstadd(token, shell->_arg, shell);
			check_for_pipe(line, shell, *token);
			free(shell->_arg);
			shell->_arg = NULL;
		}
		shell->i++;
	}
	compose_command(&shell->cmd, *token, shell, ft_lstsize(*token));
}

int			pre_parser(char *line, t_shell *shell)
{
	t_list	*token;

	shell->cmd = NULL;
	shell->i = 0;
	token = NULL;
	space_skip(line, shell);
	if (line[shell->i] == '|')
		return (error_out(shell, "syntax error near unexpected token"));
	if (check_cmd(line, shell) < 1) //check for syntax errors
		return (-1);
	main_parser(line, shell, &token);
	ft_lstclear(&token);
	if (shell->cmd == NULL)
		return (0);
	//shell->token = token;
	//init_command(shell);
	//exec_check(shell);
	//print_cmd(shell);
	//ft_lstclear(&shell->token);
	return (1);
}

int		start_shell(t_shell *shell)
{
	char *line;

	shell->status = 1;
	while (shell->status)
	{
		line = readline("[minishell]#");
		shell->err = 0;
		if (ft_strncmp(line, "vihod", ft_strlen(line) + 1) == 0)
			shell->status = 0;
		shell->flags = init_flags();
		if (pre_parser(line, shell))
		{
			add_history(line);
			//print_command(shell);
			mini_exec(&line, shell);
		}
		if (shell->cmd)
			free_command(&shell->cmd);
		if (line)
			free(line);
	}
	ft_env_clear(&shell->env);
	return (1);
}

t_flags	init_flags(void)
{
	t_flags	flags;

	flags.semi_colon = 1;
	flags.back_slash = 0;
	flags.single_q = 0;
	flags.double_q = 0;
	flags.has_env = 0;
	flags.has_pipe = 0;
	flags.has_redir = 0;
	flags.double_redir = 0;
	flags.double_out = 0;
	flags.pipe_count = 0;
	flags.pipe_in = -1;
	flags.pipe_out = -1;
	flags.out = 0;
	flags.red = 0;
	return (flags);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	shell.err = 0;
	shell.sq_err = 0;
	shell.dq_err = 0;
	shell.env_len = 0;
	shell.env_value = NULL;
	shell.env_sign = 0;
	shell._arg = NULL;
	shell.cmd_size = 0;
	init_env(envp, &shell);
	system("clear");
	start_shell(&shell);
	return (0);
}
