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

	while(line[i] != '\0') //kkkk'kkkekekekeke
	{
		if (line[i] == '\"')
		{
			shell->dq_err = 1;
			i++;
			j = i;
			while (line[i] != '\0')
			{
/* 				if (line[i] == '$')
					shell->env_sign = 1; */
/* 				if (line[i] == '$')
				{
					ft_putendl("???", 1);
					add_env_to_str(&line, shell, j);
				} */
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
	if (shell->dq_err == 1)
		error_out(shell, "syntax error double quotes");
}

int		check_cmd(char *line, int *i, t_shell *shell)
{
	int j;
	char qq;

	j = *i;
	single_quote(line, j, shell);
	double_quote(line, j, shell);
	shell->dq_err = 0;
	shell->sq_err = 0;
	*i = j;
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

/* int	check_for_env(char *line, int status)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			status = 1;

		}
		i++;
	}
	return (0);
}

int	add_env_to_str(char **line, t_shell *shell, int i)
{
	char *tmp;
	char *tmp2;
	char *env;
	int j;
	int end;

	j = i;
	//ft_putendl(line[0], 1);
	//printf("%c\n", line[0][i]);
	while (line[0][i] != '\"')
	{
		if (line[0][i] == '$')
		{
			end = i;
			tmp = ft_substr(line[0], j - 1, end);
			i++;
			while (line[0][i] != ' ' && line[0][i] != '\'' && line[0][i] != '\"'
					&& line[0][i] != '\\' && line[0][i] != '$')
					i++;
			//printf("[%c] & [%c]\n", line[0][end], line[0][i]);
			tmp2 = ft_substr(line[0], i, ft_strlen(line[0]) - i);
			env = ft_strdup(get_env(shell, line[0], end + 1, i - 1));
			//printf("tmp - [%s]\nenv - [%s]\ntmp2 - [%s]\n", tmp, env, tmp2);
			tmp = ft_strjoin(tmp, env);
			//ft_putendl("new tmp2 - ", 0);
			//ft_putendl(tmp2, 1);
			line[0] = ft_strjoin(tmp, tmp2);
			//printf("new1 - [%s]\n", str);
			//ft_putendl(line[0], 1);
			free(env);
			free(tmp);
			free(tmp2);
			//free(str);
			return (check_for_env(shell, line[0], j));
		}
		(i)++;
	}
	return (0);
} */

/* char	*env_in_quotes(char *line, t_shell *shell)
{
	int i;
	char *tmp;
	char *str;
	char *end;
	int j;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"')
		{
			str = ft_substr(line, 0, i);
			j = i;
			while (line[++i] != '\"')
			{
				if (line[i] == '$')
					shell->env_sign = 1;
			}
			tmp = ft_substr(str, j, i - j + 1);
		}
		i++;
	}
	ft_putendl(tmp, 1);
	free(tmp);
	return (NULL);
} */

void	exec_check(t_shell *shell)
{
	if (ft_strncmp(shell->cmd->cmd, "env", 3) == 0)
		ft_env(shell);
}

int			mini_parser(char *line, t_shell *shell)
{
	int i;
	t_list	*cmd;

	i = 0;
	cmd = NULL;
	space_skip(line, &i);
	if (line[i] == ';' || line[i] == '|')
		return (error_out(shell, "syntax error near unexpected token")); // ';' or '|'
	if (check_cmd(line, &i, shell) < 1) //check for syntax errors
		return (-1);
	//cmd = parse_cmd(line, &i, shell);
	while(line[i] != '\0')
	{
		if (line[i] == '\'')
			parse_single_quotes(line, &cmd, &i, shell);
		if (line[i] == '\"')
			parse_double_quotes(line, &cmd, &i, shell);
		if (line[i] == '$')
			parse_env_sign(line, &cmd, &i, shell);
/* 		if (line[i] == '\\')
			parse_back_slash(line, &cmd, &i, shell);
		if (line[i] == '>' || line[i] == '>>' || line[i] == '<')
			parse_redirect(line, &cmd, &i, shell);
		if (line[i] == '|' || line[i] == ';')
			parse_pipe_and_semicolon(line, &cmd, &i, shell); */
		//ft_putendl("YA TYT", 1);
		//printf("%c\n", line[i]);
/* 		if (line[i] == '\'')
		{
			ft_putendl("LOL", 1);
			break ;
		} */
/* 		if (line[i] == ' ')
			space_skip(line, &i); */
		else
			parse_cmd(line, &cmd, &i, shell);
		if (line[i] == '\0')
			break ;
		i++;
	}
	if (cmd == NULL)
		return (0);
	shell->cmd = cmd;
	//exec_check(shell);
	print_cmd(shell);
	ft_lstclear(&shell->cmd);
	return (1);
}

/* int	mini_exec(char **line, t_shell *shell)
{
	pid_t pid, wpid;
	int status;

	if (line[0] == NULL)
		return (1);
	pid = fork();
	if (pid == 0) // Child process
	{
		printf("input->[%s | %s]\n", line[0], line[0]);
		if (execvp(line[0], line) == -1) // change to execve
			perror("MINISHELL");
		exit(0);
	}
	else if (pid < 0) // error
		ft_putendl("Error forking\n", 0);
	else // Parent process
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
    		wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
} */

/* int		mini_cmd(t_shell *shell)
{
	if (shell->pars.has_pipe)
		do_pipe_stuff(shell); // PIPE FUNC HERE ??
	while (shell->pars.semi_colon > 0)
	{
		do_cmd_stuff(shell); // default stuff
		shell->pars.semi_colon--;
	}
} */

int		start_shell(t_shell *shell)
{
	char *line;

	shell->status = 1;
	while (shell->status)
	{
		//find_pwd(); to find and store pwd in string to display in prompt
		ft_putendl("[minishell(%%s)]# ", 0); // %s for pwd path
		get_next_line(0, &line);
		shell->err = 0;
		//printf("%s\n", line);
		//ft_putendl(line, 1);
		if (ft_strncmp(line, "vihod", 5) == 0)
			shell->status = 0;
		mini_parser(line, shell);
		//mini_cmd(shell);
		//ft_putendl(shell->cmd.cmd, 1);
		//mini_exec(&line, shell);
		//print_cmd(shell);
		//if (ft_strncmp(shell->cmd->cmd, "exit", 4) == 0)
		//		shell->status = 0;
		free(line);
		//free(shell->cmd.cmd);
		//ft_lstclear(&shell->cmd);
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
	pars.pipe_count = 0;
	return (pars);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	t_par	pars;
	//t_list	*cmd;

	//cmd->cmd = NULL;
	//cmd = NULL;
	//cmd->i = 0;
	shell.pars = init_pars();
	shell.err = 0;
	shell.sq_err = 0;
	shell.dq_err = 0;
	shell.env_len = 0;
	shell.env_value = NULL;
	shell.env_sign = 0;
	init_env(envp, &shell);
	system("clear");
	start_shell(&shell);
	return (0);
}
