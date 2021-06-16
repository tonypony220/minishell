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

	j = i;
	while(line[i] != '\0') //kkkk'kkkekekekeke
	{
		if (line[i] == '\"')
		{
			shell->dq_err = 1;
			i++;
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

/* void	print_cmd(t_shell *shell)
{
	while (shell->cmd)
	{
		ft_putendl(shell->cmd->cmd, 1);
		//printf("%s - %d\n", shell->cmd->cmd, shell->cmd->i);
		shell->cmd = shell->cmd->next;
	}
} */

void	print_cmd(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->args[i] != '\0')
	{
		ft_putendl(shell->args[i], 1);
		//printf("%s - %d\n", shell->cmd->cmd, shell->cmd->i);
		i++;
	}
}

/* void	print_cmd(t_list *cmd)
{
	while (cmd)
	{
		ft_putendl(cmd->cmd, 1);
		cmd = cmd->next;
	}
} */

char	**make_map(t_list *head, int size, t_shell *shell)
{
	char **map;
	int d;

	d = 0;	
	if (!(map = (char **)malloc((size + 1) * sizeof(char *))))
	{
		ft_putendl("ERROR", 1);
		return (NULL);
	}
	while (head)
	{
		map[d] = ft_strdup(head->cmd);
		head = head->next;
		d++;
	}
	map[d] = '\0';
	ft_lstclear(&head);
	return (map);
}

t_list	*parse_cmd(char *line, int *i, t_list *cmd, t_shell *shell)
{
	int j;
	int end;

	j = *i;
	//shell->cmd.i++;
	//printf("%s\n", line);
	while (line[*i] != ' ' && line[*i] != '\0')
	{
		if (line[*i] == ' ' || line[*i + 1] == '\0')
		{
			space_skip(line, i);
			end = *i;
			if (line[*i + 1] == '\0')
				end++;
			ft_lstadd(&cmd, line, j, end);
			j = end++;
		}
		(*i)++;
	}
	return (cmd);
	//size = ft_lstsize(cmd);
	//shell->cmd = make_map(cmd, size, shell);
	//print_cmd(cmd);
	//ft_lstclear(&cmd);
/* 	shell->cmd = cmd;
	print_cmd(shell);
	ft_lstclear(&shell->cmd); */
	//shell->cmd.cmd = ft_substr(line, j, end - j);
	//shell->cmd.c_type = 0;
	//shell->cmd.next = NULL;
}

t_list	*parse_to_list(char *line, int *i, t_shell *shell)
{
	t_list	*cmd;

	cmd = NULL;
	//parse_cmd(line, i, &cmd);
	while(line[*i] != '\0')
	{
/* 		if (line[i] == '\'')
			parse_single_quotes(line, &i, &cmd);
		if (line[i] == '\"')
			parse_double_quotes(line, &i, &cmd);
		if (line[i] == '\\')
			parse_back_slash(line, &i, &cmd);
		if (line[i] == '$')
			parse_env_sign(line, &i, &cmd);
		if (line[i] == '>' || line[i] == '>>' || line[i] == '<')
			parse_redirect(line, &i, &cmd);
		if (line[i] == '|' || line[i] == ';')
			parse_pipe_and_semicolon(line, &i, &cmd);
		else
			parse_cmd(line, &i, &cmd); */
		cmd = parse_cmd(line, i, cmd, shell);
		(*i)++;
	}
	shell->arg_size = ft_lstsize(cmd);
	shell->args = make_map(cmd, shell->arg_size, shell);
	ft_lstclear(&cmd);
	return (cmd);
}

void	clear_map(char **map, int size)
{
	while (size >= 0)
	{
		if (map[size])
			free(map[size]);
		size--;
	}
	if (map)
		free(map);
}

int			mini_parser(char *line, t_shell *shell)
{
	int i;

	i = 0;
	if (line == NULL)
		return (0);
	space_skip(line, &i);
	if (line[i] == ';' || line[i] == '|')
		return (error_out(shell, "syntax error near unexpected token")); // ';' or '|'
	if (check_cmd(line, &i, shell) < 1) //check for syntax errors
		return (-1);
	//parse_cmd(line, &i, shell);
	//shell->cmd = parse_to_list(line, &i, shell);
	parse_to_list(line, &i, shell);
	print_cmd(shell);
	clear_map(shell->args, shell->arg_size);
	//ft_lstclear(&shell->cmd);
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
// 									^MINI_CMD^

int		start_shell(t_shell *shell)
{
	char *line;

	shell->status = 1;
	while (shell->status)
	{
		//find_pwd(); to find and store pwd in string to display in prompt
		ft_putendl("[minishell(%%s)]# ", 0); // %s for pwd path
		get_next_line(0, &line);
		//printf("%s\n", line);
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

int	main(int ac, char **av, char **env)
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
	system("clear");
	start_shell(&shell);
	return (0);
}