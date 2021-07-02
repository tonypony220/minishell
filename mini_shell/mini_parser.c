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

int		check_cmd(char *line, t_shell *shell)
{
	int j;
	char qq;

	j = shell->i;
	single_quote(line, j, shell);
	double_quote(line, j, shell);
	shell->dq_err = 0;
	shell->sq_err = 0;
	shell->i = j;
	if (shell->err == -1)
		return (-1);
	return (1);
}

void	print_cmd(t_shell *shell)
{
	while (shell->cmd)
	{
		ft_putendl(shell->cmd->cmd, 1);
		shell->cmd = shell->cmd->next;
	}
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
	if (line[0][i + 1] == '\0' || shell->pars.double_q == 0) // SegFault with single $
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
			while (ft_strchr(" \'\"\\$;:", line[i]) == 0)
					i++;
			tmp2 = ft_substr(line, i, ft_strlen(line) - i);
			if (get_env(shell, line, end + 1, i - 1) == 1)
				env = ft_strdup(shell->env_value);
			free_env_shell(shell);
			tmp = ft_strjoin(tmp, env);
			tmp = ft_strjoin(tmp, tmp2);
			free(env);
			free(tmp2);
			return (tmp);
		}
		(i)++;
	}
	return (line);
}

void	exec_check(t_shell *shell)
{
	if (ft_strncmp(shell->cmd->cmd, "env", 3) == 0)
		ft_env(shell);
}

void	main_parser(char *line, t_shell *shell, t_list **cmd)
{
	while(line[shell->i] != '\0')
	{
		if (line[shell->i] == '\'')
			parse_single_quotes(line, shell);
		else if (line[shell->i] == '\"')
			parse_double_quotes(line, shell);
		else if (line[shell->i] == '$')
			parse_env_sign(line, shell);
/* 		else if (line[i] == '>' || line[i] == '>>' || line[i] == '<')
			parse_redirect(line, &cmd, shell);
		else if (line[i] == '|' || line[i] == ';')
			parse_pipe_and_semicolon(line, &cmd, shell); */
		else
			parse_cmd(line, shell);
		if (line[shell->i + 1] == ' ' || line[shell->i + 1] == '\0')
		{
			ft_lstadd(cmd, shell->_arg, shell);
			free(shell->_arg);
			shell->_arg = NULL;
		}
		shell->i++;
	}
}

int			pre_parser(char *line, t_shell *shell)
{
	t_list	*cmd;

	shell->i = 0;
	cmd = NULL;
	space_skip(line, shell);
	if (line[shell->i] == '|')
		return (error_out(shell, "syntax error near unexpected token"));
	if (check_cmd(line, shell) < 1) //check for syntax errors
		return (-1);
	main_parser(line, shell, &cmd);
	if (cmd == NULL)
		return (0);
	shell->cmd = cmd;
	//exec_check(shell);
	print_cmd(shell);
	ft_lstclear(&shell->cmd);
	return (1);
}

int		start_shell(t_shell *shell)
{
	char *line;

	shell->status = 1;
	while (shell->status)
	{
		//find_pwd(); to find and store pwd in string to display in prompt
		ft_putendl("[minishell]# ", 0);
		get_next_line(0, &line);
		shell->err = 0;
		if (ft_strncmp(line, "vihod", 5) == 0)
			shell->status = 0;
		pre_parser(line, shell);
		//mini_cmd(shell);
		//mini_exec(&line, shell);
		//if (ft_strncmp(shell->cmd->cmd, "exit", 4) == 0)
		//		shell->status = 0;
		free(line);
	}
	ft_env_clear(&shell->env);
	return (1);
}

t_par	init_pars(void)
{
	t_par	pars;

	pars.semi_colon = 1;
	pars.back_slash = 0;
	pars.single_q = 0;
	pars.double_q = 0;
	pars.has_env = 0;
	pars.has_pipe = 0;
	pars.has_redir = 0;
	pars.double_redir = 0;
	pars.double_out = 0;
	pars.pipe_count = 0;
	pars.out = 0;
	pars.red = 0;
	return (pars);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	t_par	pars;

	shell.pars = init_pars();
	shell.err = 0;
	shell.sq_err = 0;
	shell.dq_err = 0;
	shell.env_len = 0;
	shell.env_value = NULL;
	shell.env_sign = 0;
	shell._arg = NULL;
	init_env(envp, &shell);
	system("clear");
	start_shell(&shell);
	return (0);
}
